/*
    Training Module
        -Fomobot Core
            Highalnder

    Goals:
        Take over the world

 */
//import log from './logger'

import log from './logger'
import {fomoTrain,fomoPath,backtestDir} from './config'

const TAG = " | TRAIN | "

const {ipcMain} = require('electron')

var tb = require('timebucket')
    , minimist = require('minimist')
    , fs = require('fs')
    , path = require('path')
    , spawn = require('child_process').spawn
    , moment = require('moment')
    // eslint-disable-next-line no-unused-vars
    , colors = require('colors')
    , analytics = require('forex-analytics-fomo')
    , ProgressBar = require('progress')
    , crypto = require('crypto')
    , objectifySelector = require('./lib/objectify-selector')
    , engineFactory = require('./lib/engine')
    , collectionService = require('./lib/services/collection-service')


var EventEmitter = require('events')

var fa_defaultIndicators = [
    'CCI',
    'MACD',
    'RSI',
    'SAR',
    'Stochastic'
]

var fa_availableIndicators = [
    'ATR',
    'BOP',
    'CCI',
    'MACD',
    'MACD_Signal',
    'MACD_Histogram',
    'Momentum',
    'RSI',
    'SAR',
    'SMA15_SMA50',
    'Stochastic'
]


function fa_getTrainOptions (so) {
    if (typeof(so) === 'undefined') so = {}

    return {
        populationCount: so.populationCount || 100,
        generationCount: so.generationCount || 100,
        selectionAmount: so.selectionAmount || 10,
        leafValueMutationProbability: so.leafValueMutationProbability || 0.5,
        leafSignMutationProbability: so.leafSignMutationProbability || 0.3,
        logicalNodeMutationProbability: so.logicalNodeMutationProbability || 0.3,
        leafIndicatorMutationProbability: so.leafIndicatorMutationProbability || 0.2,
        crossoverProbability: so.crossoverProbability || 0.03,
        indicators: so.indicators ? so.indicators.split(',') : fa_defaultIndicators
    }
}

var conf = require('./conf')

let zenbot = {}
zenbot.conf = conf

var authStr = '', authMechanism, connectionString

if(zenbot.conf.mongo.username){
    authStr = encodeURIComponent(zenbot.conf.mongo.username)

    if(zenbot.conf.mongo.password) authStr += ':' + encodeURIComponent(zenbot.conf.mongo.password)

    authStr += '@'

    // authMechanism could be a conf.js parameter to support more mongodb authentication methods
    authMechanism = zenbot.conf.mongo.authMechanism || 'DEFAULT'
}

var connectionString = 'mongodb://' + authStr + zenbot.conf.mongo.host + ':' + zenbot.conf.mongo.port + '/' + zenbot.conf.mongo.db + '?' +
    (zenbot.conf.mongo.replicaSet ? '&replicaSet=' + zenbot.conf.mongo.replicaSet : '' ) +
    (authMechanism ? '&authMechanism=' + authMechanism : '' )


let dbClient

// let init = async function(){
//     require('mongodb').MongoClient.connect(connectionString, { useNewUrlParser: true }, function (err, client) {
//         let tag = TAG + " | AfterMongo | "
//         if (err) {
//             console.error('WARNING: MongoDB Connection Error: ', err)
//             console.error('WARNING: without MongoDB some features (such as backfilling/simulation) may be disabled.')
//             console.error('Attempted authentication string: ' + connectionString)
//             cb(null, zenbot)
//             return
//         }
//
//         dbClient = client
//         return client
//     })
// }
//




let train = function(ipcEvent){
    try{
        require('mongodb').MongoClient.connect(connectionString, { useNewUrlParser: true }, function (err, client) {
            let tag = TAG + " | AfterMongo | "
            if (err) {
                console.error('WARNING: MongoDB Connection Error: ', err)
                console.error('WARNING: without MongoDB some features (such as backfilling/simulation) may be disabled.')
                console.error('Attempted authentication string: ' + connectionString)
                cb(null, zenbot)
                return
            }

            //console.log(client)
            var db = client.db('zenbot4')

            var eventBus = new EventEmitter()
            ipcEvent.sender.send('bot',"message","starting training!")

            let cmd = {}
            let conf = require('./conf.js')
            conf.eventBus = eventBus
            conf.db = {}
            conf.db.mongo = db
            //console.log(tag,conf.db)

            var s = {options: minimist(process.argv)}
            var so = s.options
            delete so._
            if (cmd.conf) {
                var overrides = require(path.resolve(process.cwd(), cmd.conf))
                Object.keys(overrides).forEach(function (k) {
                    so[k] = overrides[k]
                })
            }
            Object.keys(conf).forEach(function (k) {
                if (typeof cmd[k] !== 'undefined') {
                    so[k] = cmd[k]
                }
            })
            var tradesCollection = collectionService(conf).getTrades()
            if (!so.days_test) { so.days_test = 0 }
            so.strategy = 'noop'

            var unknownIndicators = []
            if (so.indicators) {
                so.indicators.split(',').forEach(function(indicator) {
                    if (!fa_availableIndicators.includes(indicator))
                        unknownIndicators.push(indicator)
                })
            }
            if (unknownIndicators.length > 0) {
                console.error(('ERROR: The following indicators are not in forex.analytics: ').red + (unknownIndicators.toString()).yellow)
                console.error('Available indicators: ' + fa_availableIndicators.toString())
                process.exit(1)
            }

            if (so.start_training) {
                so.start_training = moment(so.start_training).valueOf()
                if (so.days_training && !so.end_training) {
                    so.end_training = tb(so.start_training).resize('1d').add(so.days_training).toMilliseconds()
                }
            }
            if (so.end_training) {
                so.end_training = moment(so.end_training).valueOf()
                if (so.days_training && !so.start_training) {
                    so.start_training = tb(so.end_training).resize('1d').subtract(so.days_training).toMilliseconds()
                }
            }
            if (!so.start_training && so.days_training) {
                var d = tb('1d')
                so.start_training = d.subtract(so.days_training).toMilliseconds()
            }

            //Selector (Market?)  gdax.BTC-USD
            so.selector = objectifySelector( conf.selector)
            so.mode = 'train'

            conf.ipcEvent = ipcEvent

            var engine = engineFactory(s, conf)

            if (!so.min_periods) so.min_periods = 1
            var cursor, reversing, reverse_point
            var query_start = so.start_training ? tb(so.start_training).resize(so.period_length).subtract(so.min_periods + 2).toMilliseconds() : null

            function writeTempModel (strategy) {
                let tag = TAG + " | writeTempModel  | "
                log.debug(tag, "checkpoint")

                var tempModelString = JSON.stringify(
                    {
                        'selector': so.selector.normalized,
                        'period': so.period_length,
                        'start_training': moment(so.start_training),
                        'end_training': moment(so.end_training),
                        'options': fa_getTrainOptions(so),
                        'strategy': strategy
                    }, null, 4)

                var tempModelHash = crypto.createHash('sha256').update(tempModelString).digest('hex')
                //
                var tempModelFile = fomoTrain+'/models/temp.' + tempModelHash + '-' + moment(so.start_training).utc().format('YYYYMMDD_HHmmssZZ') + '.json'
                //var tempModelFile = './models/temp.' + tempModelHash + '-' + moment(so.start_training).utc().format('YYYYMMDD_HHmmssZZ') + '.json'

                log.debug(tag,"tempModelFile: ",tempModelFile)
                log.debug(tag,"tempModelHash: ",tempModelHash)

                let resultWrite = fs.writeFileSync(
                    tempModelFile,
                    tempModelString
                )

                log.debug("resultWrite: ",resultWrite)

                return tempModelFile
            }

            function writeFinalModel (strategy, end_training, trainingResult, testResult) {
                let tag = TAG + " | writeFinalModel  | "
                log.debug(tag, "checkpoint")

                var finalModelString = JSON.stringify(
                    {
                        'selector': so.selector.normalized,
                        'period': so.period_length,
                        'start_training': moment(so.start_training).utc(),
                        'end_training': moment(end_training).utc(),
                        'result_training': trainingResult,
                        'start_test': so.days_test > 0 ? moment(end_training).utc() : undefined,
                        'result_test': testResult,
                        'options': fa_getTrainOptions(so),
                        'strategy': strategy
                    }, null, 4)

                var testVsBuyHold = typeof(testResult) !== 'undefined' ? testResult.vsBuyHold : 'noTest'

                var finalModelFile = 'models/forex.model_' + so.selector.normalized
                    + '_period=' + so.period_length
                    + '_from=' + moment(so.start_training).utc().format('YYYYMMDD_HHmmssZZ')
                    + '_to=' + moment(end_training).utc().format('YYYYMMDD_HHmmssZZ')
                    + '_trainingVsBuyHold=' + trainingResult.vsBuyHold
                    + '_testVsBuyHold=' + testVsBuyHold
                    + '_created=' + moment().utc().format('YYYYMMDD_HHmmssZZ')
                    + '.json'

                fs.writeFileSync(
                    finalModelFile,
                    finalModelString
                )

                return finalModelFile
            }

            function parseSimulation (simulationResultFile) {
                let tag = TAG + " | parseSimulation  | "
                log.debug(tag, "checkpoint")
                var endBalance = new RegExp(/end balance: .* \((.*)%\)/)
                var buyHold = new RegExp(/buy hold: .* \((.*)%\)/)
                var vsBuyHold = new RegExp(/vs\. buy hold: (.*)%/)
                var trades = new RegExp(/([0-9].* trades over .* days \(avg (.*) trades\/day\))/)
                var errorRate = new RegExp(/error rate: (.*)%/)

                var simulationResult = fs.readFileSync(simulationResultFile).toString()
                simulationResult = simulationResult.substr(simulationResult.length - 512)

                var result = {}
                if (simulationResult.match(endBalance)) { result.endBalance      = simulationResult.match(endBalance)[1] }
                if (simulationResult.match(buyHold))    { result.buyHold         = simulationResult.match(buyHold)[1] }
                if (simulationResult.match(vsBuyHold))  { result.vsBuyHold       = simulationResult.match(vsBuyHold)[1] }
                if (simulationResult.match(trades)) {
                    result.trades          = simulationResult.match(trades)[1]
                    result.avgTradesPerDay = simulationResult.match(trades)[2]
                }
                if (simulationResult.match(errorRate))  { result.errorRate       = simulationResult.match(errorRate)[1] }

                return result
            }

            function trainingDone (strategy, lastPeriod) {
                let tag = TAG + " | trainingDone  | "
                log.debug(tag, "checkpoint")
                var tempModelFile = writeTempModel(strategy)
                //console.log(tag,'\nModel temporarily written to ' + tempModelFile)
                ipcEvent.sender.send('bot',"message",'Model temporarily written to ' + tempModelFile)


                if (typeof(so.end_training) === 'undefined') {
                    so.end_training = lastPeriod.time * 1000
                }


                ipcEvent.sender.send('bot',"message",'\nRunning simulation on training data from '
                    + moment(so.start_training).format('YYYY-MM-DD HH:mm:ss ZZ') + ' to '
                    + moment(so.end_training).format('YYYY-MM-DD HH:mm:ss ZZ') + '.\n')

                // console.log(tag,
                //     '\nRunning simulation on training data from '
                //     + moment(so.start_training).format('YYYY-MM-DD HH:mm:ss ZZ') + ' to '
                //     + moment(so.end_training).format('YYYY-MM-DD HH:mm:ss ZZ') + '.\n'
                // )

                var zenbot_cmd = process.platform === 'win32' ? 'zenbot.bat' : 'zenbot.sh' // Use 'win32' for 64 bit windows too
                log.debug(tag,"zenbot_cmd: ",zenbot_cmd)

                var trainingArgs = [
                    'sim',
                    so.selector.normalized,
                    '--strategy', 'forex_analytics',
                    '--disable_options',
                    '--modelfile', path.join(fomoPath, '..', tempModelFile),
                    '--start', moment(so.start_training).format('YYYYMMDDHHmm'),
                    '--end', moment(so.end_training).format('YYYYMMDDHHmm'),
                    '--period', so.period_length,
                    '--filename', path.join(backtestDir, '..', tempModelFile) + '-simTrainingResult.html'
                ]

                let workToDo = trainingArgs
                log.debug(tag,"workToDo: ",workToDo)

                return workToDo
            }

            function createStrategy (candlesticks) {
                let tag = TAG + " | createStrategy  | "
                log.debug(tag, "checkpoint")

                var bar = new ProgressBar(
                    'Training [:bar] :percent :etas - Fitness: :fitness',
                    {
                        width: 80,
                        total: fa_getTrainOptions(so).generationCount,
                        incomplete: ' '
                    }
                )

                return analytics.findStrategy(candlesticks, fa_getTrainOptions(so), function(strategy, fitness/*, generation*/) {
                    bar.tick({
                        'fitness': fitness
                    })
                })
            }

            function createCandlesticks () {
                let tag = TAG + " | createCandlesticks  | "
                log.debug(tag, "checkpoint")

                if (!s.period) {
                    console.error('no trades found! try running `zenbot backfill ' + so.selector.normalized + '` first')
                    process.exit(1)
                }

                var option_keys = Object.keys(so)
                option_keys.sort(function (a, b) {
                    if (a < b) return -1
                    return 1
                })
                var options = {}
                option_keys.forEach(function (k) {
                    options[k] = so[k]
                })

                var candlesticks = []
                s.lookback.unshift(s.period)
                s.lookback.slice(0, s.lookback.length - so.min_periods).map(function (period) {
                    var candlestick = {
                        open: period.open,
                        high: period.high,
                        low: period.low,
                        close: period.close,
                        time: period.time / 1000
                    }
                    candlesticks.unshift(candlestick)
                })

                createStrategy(candlesticks)
                    .then(function(strategy) {
                        log.debug(tag, "createStrategy checkpoint END")
                        let work = trainingDone(strategy, candlesticks[candlesticks.length - 1])
                        return work
                    })
                    .catch(function(err) {
                        log.error(tag,('Training error. Aborting.').red)
                        log.error(tag,err)
                        //process.exit(1)
                    })
            }

            function getTrades () {
                let tag = TAG + " | getTrades  | "
                //log.debug(tag, "checkpoint")

                var opts = {
                    query: {
                        selector: so.selector.normalized
                    },
                    sort: {time: 1},
                    limit: 1000
                }

                if (so.end_training) {
                    opts.query.time = {$lte: so.end_training}
                }
                if (cursor) {
                    if (reversing) {
                        opts.query.time = {}
                        opts.query.time['$lt'] = cursor
                        if (query_start) {
                            opts.query.time['$gte'] = query_start
                        }
                        opts.sort = {time: -1}
                    }
                    else {
                        if (!opts.query.time) opts.query.time = {}
                        opts.query.time['$gt'] = cursor
                    }
                }
                else if (query_start) {
                    if (!opts.query.time) opts.query.time = {}
                    opts.query.time['$gte'] = query_start
                }
                tradesCollection.find(opts.query).limit(opts.limit).sort(opts.sort).toArray(function (err, trades) {
                    if (err) throw err
                    if (!trades.length) {
                        if (so.symmetrical && !reversing) {
                            reversing = true
                            reverse_point = cursor
                            return getTrades()
                        }
                        let result = createCandlesticks()
                        return result
                    }
                    if (so.symmetrical && reversing) {
                        trades.forEach(function (trade) {
                            trade.orig_time = trade.time
                            trade.time = reverse_point + (reverse_point - trade.time)
                        })
                    }
                    engine.update(trades, function (err) {
                        if (err) throw err
                        cursor = trades[trades.length - 1].time
                        setImmediate(getTrades)
                    })
                })
            }
            getTrades()
        })
    }catch(e){
        console.error(e)
    }
}


//console.log(tag,'Generating training candlesticks from database...')
//getTrades()

// export default {
// //    init,
//     train
// }
module.exports = ({train})
