/* TA-LIB Copyright (c) 1999-2008, Mario Fortier
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 *
 * - Neither name of author nor the names of its contributors
 *   may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* List of contributors:
 *
 *  Initial  Name/description
 *  -------------------------------------------------------------------
 *  MF       Mario Fortier
 *
 *
 * Change history:
 *
 *  MMDDYY BY   Description
 *  -------------------------------------------------------------------
 *  112400 MF   Template creation.
 *  052603 MF   Adapt code to compile with .NET Managed C++
 *
 */

/**** START GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
/* All code within this section is automatically
 * generated by gen_code. Any modification will be lost
 * next time gen_code is run.
 */
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */    #include "TA-Lib-Core.h"
/* Generated */    #define TA_INTERNAL_ERROR(Id) (RetCode::InternalError)
/* Generated */    namespace TicTacTec { namespace TA { namespace Library {
/* Generated */ #elif defined( _JAVA )
/* Generated */    #include "ta_defs.h"
/* Generated */    #include "ta_java_defs.h"
/* Generated */    #define TA_INTERNAL_ERROR(Id) (RetCode.InternalError)
/* Generated */ #else
/* Generated */    #include <string.h>
/* Generated */    #include <math.h>
/* Generated */    #include "ta_func.h"
/* Generated */ #endif
/* Generated */ 
/* Generated */ #ifndef TA_UTILITY_H
/* Generated */    #include "ta_utility.h"
/* Generated */ #endif
/* Generated */ 
/* Generated */ #ifndef TA_MEMORY_H
/* Generated */    #include "ta_memory.h"
/* Generated */ #endif
/* Generated */ 
/* Generated */ #define TA_PREFIX(x) TA_##x
/* Generated */ #define INPUT_TYPE   double
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ int Core::TemaLookback( int           optInTimePeriod )  /* From 2 to 100000 */
/* Generated */ 
/* Generated */ #elif defined( _JAVA )
/* Generated */ public int temaLookback( int           optInTimePeriod )  /* From 2 to 100000 */
/* Generated */ 
/* Generated */ #else
/* Generated */ int TA_TEMA_Lookback( int           optInTimePeriod )  /* From 2 to 100000 */
/* Generated */ 
/* Generated */ #endif
/**** END GENCODE SECTION 1 - DO NOT DELETE THIS LINE ****/
{
   /* insert local variable here */
    int retValue;

/**** START GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/
/* Generated */ #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */    /* min/max are checked for optInTimePeriod. */
/* Generated */    if( (int)optInTimePeriod == TA_INTEGER_DEFAULT )
/* Generated */       optInTimePeriod = 30;
/* Generated */    else if( ((int)optInTimePeriod < 2) || ((int)optInTimePeriod > 100000) )
/* Generated */       return -1;
/* Generated */ 
/* Generated */ #endif /* TA_FUNC_NO_RANGE_CHECK */
/**** END GENCODE SECTION 2 - DO NOT DELETE THIS LINE ****/

   /* insert lookback code here. */

   /* Get lookack for one EMA. */
   retValue = LOOKBACK_CALL(EMA)( optInTimePeriod );

   return retValue * 3;
}

/**** START GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/
/*
 * TA_TEMA - Triple Exponential Moving Average
 * 
 * Input  = double
 * Output = double
 * 
 * Optional Parameters
 * -------------------
 * optInTimePeriod:(From 2 to 100000)
 *    Number of period
 * 
 * 
 */
/* Generated */ 
/* Generated */ #if defined( _MANAGED ) && defined( USE_SUBARRAY )
/* Generated */ enum class Core::RetCode Core::Tema( int    startIdx,
/* Generated */                                      int    endIdx,
/* Generated */                                      SubArray<double>^ inReal,
/* Generated */                                      int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                                      [Out]int%    outBegIdx,
/* Generated */                                      [Out]int%    outNBElement,
/* Generated */                                      SubArray<double>^  outReal )
/* Generated */ #elif defined( _MANAGED )
/* Generated */ enum class Core::RetCode Core::Tema( int    startIdx,
/* Generated */                                      int    endIdx,
/* Generated */                                      cli::array<double>^ inReal,
/* Generated */                                      int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                                      [Out]int%    outBegIdx,
/* Generated */                                      [Out]int%    outNBElement,
/* Generated */                                      cli::array<double>^  outReal )
/* Generated */ #elif defined( _JAVA )
/* Generated */ public RetCode tema( int    startIdx,
/* Generated */                      int    endIdx,
/* Generated */                      double       inReal[],
/* Generated */                      int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                      MInteger     outBegIdx,
/* Generated */                      MInteger     outNBElement,
/* Generated */                      double        outReal[] )
/* Generated */ #else
/* Generated */ TA_RetCode TA_TEMA( int    startIdx,
/* Generated */                     int    endIdx,
/* Generated */                     const double inReal[],
/* Generated */                     int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                     int          *outBegIdx,
/* Generated */                     int          *outNBElement,
/* Generated */                     double        outReal[] )
/* Generated */ #endif
/**** END GENCODE SECTION 3 - DO NOT DELETE THIS LINE ****/
{
   /* Insert local variables here. */
   ARRAY_REF(firstEMA);
   ARRAY_REF(secondEMA);
   double k;

   VALUE_HANDLE_INT(firstEMABegIdx);
   VALUE_HANDLE_INT(firstEMANbElement);
   VALUE_HANDLE_INT(secondEMABegIdx);
   VALUE_HANDLE_INT(secondEMANbElement);
   VALUE_HANDLE_INT(thirdEMABegIdx);
   VALUE_HANDLE_INT(thirdEMANbElement);

   int tempInt, outIdx, lookbackTotal, lookbackEMA;
   int firstEMAIdx, secondEMAIdx;

   ENUM_DECLARATION(RetCode) retCode;

/**** START GENCODE SECTION 4 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */ 
/* Generated */    /* Validate the requested output range. */
/* Generated */    if( startIdx < 0 )
/* Generated */       return ENUM_VALUE(RetCode,TA_OUT_OF_RANGE_START_INDEX,OutOfRangeStartIndex);
/* Generated */    if( (endIdx < 0) || (endIdx < startIdx))
/* Generated */       return ENUM_VALUE(RetCode,TA_OUT_OF_RANGE_END_INDEX,OutOfRangeEndIndex);
/* Generated */ 
/* Generated */    #if !defined(_JAVA)
/* Generated */    if( !inReal ) return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */    #endif /* !defined(_JAVA)*/
/* Generated */    /* min/max are checked for optInTimePeriod. */
/* Generated */    if( (int)optInTimePeriod == TA_INTEGER_DEFAULT )
/* Generated */       optInTimePeriod = 30;
/* Generated */    else if( ((int)optInTimePeriod < 2) || ((int)optInTimePeriod > 100000) )
/* Generated */       return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */ 
/* Generated */    #if !defined(_JAVA)
/* Generated */    if( !outReal )
/* Generated */       return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */ 
/* Generated */    #endif /* !defined(_JAVA) */
/* Generated */ #endif /* TA_FUNC_NO_RANGE_CHECK */
/* Generated */ 
/**** END GENCODE SECTION 4 - DO NOT DELETE THIS LINE ****/

   /* Insert TA function code here. */

   /* For an explanation of this function, please read:
    * 
    * Stocks & Commodities V. 12:1 (11-19): 
    *   Smoothing Data With Faster Moving Averages
    * Stocks & Commodities V. 12:2 (72-80): 
    *   Smoothing Data With Less Lag
    *
    * Both magazine articles written by Patrick G. Mulloy
    *
    * Essentially, a TEMA of time serie 't' is:
    *   EMA1 = EMA(t,period)
    *   EMA2 = EMA(EMA(t,period),period)
    *   EMA3 = EMA(EMA(EMA(t,period),period))
    *   TEMA = 3*EMA1 - 3*EMA2 + EMA3
    *
    * TEMA offers a moving average with less lags then the
    * traditional EMA.
    *
    * Do not confuse a TEMA with EMA3. Both are called "Triple EMA"
    * in the litterature.
    *
    * DEMA is very similar (and from the same author).
    */

   /* Will change only on success. */
   VALUE_HANDLE_DEREF_TO_ZERO(outNBElement);
   VALUE_HANDLE_DEREF_TO_ZERO(outBegIdx);

   /* Adjust startIdx to account for the lookback period. */
   lookbackEMA = LOOKBACK_CALL(EMA)( optInTimePeriod );
   lookbackTotal = lookbackEMA * 3;

   if( startIdx < lookbackTotal )
      startIdx = lookbackTotal;

   /* Make sure there is still something to evaluate. */
   if( startIdx > endIdx )
      return ENUM_VALUE(RetCode,TA_SUCCESS,Success); 

   /* Allocate a temporary buffer for the firstEMA. */
   tempInt = lookbackTotal+(endIdx-startIdx)+1;
   ARRAY_ALLOC(firstEMA,tempInt);
   #if !defined( _JAVA )
      if( !firstEMA )
         return ENUM_VALUE(RetCode,TA_ALLOC_ERR,AllocErr);
   #endif

   /* Calculate the first EMA */   
   k = PER_TO_K(optInTimePeriod);
   retCode = FUNCTION_CALL(INT_EMA)( startIdx-(lookbackEMA*2), endIdx, inReal,
                                     optInTimePeriod, k,
                                     VALUE_HANDLE_OUT(firstEMABegIdx), VALUE_HANDLE_OUT(firstEMANbElement),
                     firstEMA );
   
   /* Verify for failure or if not enough data after
    * calculating the first EMA.
    */
   if( (retCode != ENUM_VALUE(RetCode,TA_SUCCESS,Success) ) || (VALUE_HANDLE_GET(firstEMANbElement) == 0) )
   {
      ARRAY_FREE( firstEMA );
      return retCode;
   }

   /* Allocate a temporary buffer for storing the EMA2 */
   ARRAY_ALLOC(secondEMA,VALUE_HANDLE_GET(firstEMANbElement));
   #if !defined( _JAVA ) && !defined( USE_SUBARRAY )
      if( !secondEMA )
      {
         ARRAY_FREE( firstEMA );
         return ENUM_VALUE(RetCode,TA_ALLOC_ERR,AllocErr);
      }   
   #endif

   retCode = FUNCTION_CALL_DOUBLE(INT_EMA)( 0, VALUE_HANDLE_GET(firstEMANbElement)-1, firstEMA,
                                            optInTimePeriod, k,
                                            VALUE_HANDLE_OUT(secondEMABegIdx), VALUE_HANDLE_OUT(secondEMANbElement), 
                                secondEMA );

   /* Return empty output on failure or if not enough data after
    * calculating the second EMA.
    */
   if( (retCode != ENUM_VALUE(RetCode,TA_SUCCESS,Success) ) || (VALUE_HANDLE_GET(secondEMANbElement) == 0) )      
   {
      ARRAY_FREE( firstEMA );
      ARRAY_FREE( secondEMA );
      return retCode;
   }

   /* Calculate the EMA3 into the caller provided output. */
   retCode = FUNCTION_CALL_DOUBLE(INT_EMA)( 0, VALUE_HANDLE_GET(secondEMANbElement)-1, secondEMA,
                                            optInTimePeriod, k,
                                            VALUE_HANDLE_OUT(thirdEMABegIdx), VALUE_HANDLE_OUT(thirdEMANbElement),
                                            outReal );

   /* Return empty output on failure or if not enough data after
    * calculating the third EMA.
    */
   if( (retCode != ENUM_VALUE(RetCode,TA_SUCCESS,Success) ) || (VALUE_HANDLE_GET(thirdEMANbElement) == 0) )
   {
      ARRAY_FREE( firstEMA );
      ARRAY_FREE( secondEMA );
      return retCode;
   }

   /* Indicate where the output starts relative to
    * the caller input.
    */
   firstEMAIdx  = VALUE_HANDLE_GET(thirdEMABegIdx) + VALUE_HANDLE_GET(secondEMABegIdx);
   secondEMAIdx = VALUE_HANDLE_GET(thirdEMABegIdx);
   VALUE_HANDLE_DEREF(outBegIdx) = firstEMAIdx + VALUE_HANDLE_GET(firstEMABegIdx);

   /* Do the TEMA:
    *  Iterate through the EMA3 (output buffer) and adjust
    *  the value by using the EMA2 and EMA1.
    */
   outIdx = 0;
   while( outIdx < VALUE_HANDLE_GET(thirdEMANbElement) ) 
   {
      outReal[outIdx] += (3.0*firstEMA[firstEMAIdx++]) - (3.0*secondEMA[secondEMAIdx++]);
      outIdx++;
   }

   ARRAY_FREE( firstEMA );
   ARRAY_FREE( secondEMA );

   /* Indicates to the caller the number of output
    * successfully calculated.
    */
   VALUE_HANDLE_DEREF(outNBElement) = outIdx;

   return ENUM_VALUE(RetCode,TA_SUCCESS,Success);
}


/**** START GENCODE SECTION 5 - DO NOT DELETE THIS LINE ****/
/* Generated */ 
/* Generated */ #define  USE_SINGLE_PRECISION_INPUT
/* Generated */ #undef  TA_LIB_PRO
/* Generated */ #if !defined( _MANAGED ) && !defined( _JAVA )
/* Generated */    #undef   TA_PREFIX
/* Generated */    #define  TA_PREFIX(x) TA_S_##x
/* Generated */ #endif
/* Generated */ #undef   INPUT_TYPE
/* Generated */ #define  INPUT_TYPE float
/* Generated */ #if defined( _MANAGED ) && defined( USE_SUBARRAY )
/* Generated */ enum class Core::RetCode Core::Tema( int    startIdx,
/* Generated */                                      int    endIdx,
/* Generated */                                      SubArray<float>^ inReal,
/* Generated */                                      int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                                      [Out]int%    outBegIdx,
/* Generated */                                      [Out]int%    outNBElement,
/* Generated */                                      SubArray<double>^  outReal )
/* Generated */ #elif defined( _MANAGED )
/* Generated */ enum class Core::RetCode Core::Tema( int    startIdx,
/* Generated */                                      int    endIdx,
/* Generated */                                      cli::array<float>^ inReal,
/* Generated */                                      int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                                      [Out]int%    outBegIdx,
/* Generated */                                      [Out]int%    outNBElement,
/* Generated */                                      cli::array<double>^  outReal )
/* Generated */ #elif defined( _JAVA )
/* Generated */ public RetCode tema( int    startIdx,
/* Generated */                      int    endIdx,
/* Generated */                      float        inReal[],
/* Generated */                      int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                      MInteger     outBegIdx,
/* Generated */                      MInteger     outNBElement,
/* Generated */                      double        outReal[] )
/* Generated */ #else
/* Generated */ TA_RetCode TA_S_TEMA( int    startIdx,
/* Generated */                       int    endIdx,
/* Generated */                       const float  inReal[],
/* Generated */                       int           optInTimePeriod, /* From 2 to 100000 */
/* Generated */                       int          *outBegIdx,
/* Generated */                       int          *outNBElement,
/* Generated */                       double        outReal[] )
/* Generated */ #endif
/* Generated */ {
/* Generated */    ARRAY_REF(firstEMA);
/* Generated */    ARRAY_REF(secondEMA);
/* Generated */    double k;
/* Generated */    VALUE_HANDLE_INT(firstEMABegIdx);
/* Generated */    VALUE_HANDLE_INT(firstEMANbElement);
/* Generated */    VALUE_HANDLE_INT(secondEMABegIdx);
/* Generated */    VALUE_HANDLE_INT(secondEMANbElement);
/* Generated */    VALUE_HANDLE_INT(thirdEMABegIdx);
/* Generated */    VALUE_HANDLE_INT(thirdEMANbElement);
/* Generated */    int tempInt, outIdx, lookbackTotal, lookbackEMA;
/* Generated */    int firstEMAIdx, secondEMAIdx;
/* Generated */    ENUM_DECLARATION(RetCode) retCode;
/* Generated */  #ifndef TA_FUNC_NO_RANGE_CHECK
/* Generated */     if( startIdx < 0 )
/* Generated */        return ENUM_VALUE(RetCode,TA_OUT_OF_RANGE_START_INDEX,OutOfRangeStartIndex);
/* Generated */     if( (endIdx < 0) || (endIdx < startIdx))
/* Generated */        return ENUM_VALUE(RetCode,TA_OUT_OF_RANGE_END_INDEX,OutOfRangeEndIndex);
/* Generated */     #if !defined(_JAVA)
/* Generated */     if( !inReal ) return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */     #endif 
/* Generated */     if( (int)optInTimePeriod == TA_INTEGER_DEFAULT )
/* Generated */        optInTimePeriod = 30;
/* Generated */     else if( ((int)optInTimePeriod < 2) || ((int)optInTimePeriod > 100000) )
/* Generated */        return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */     #if !defined(_JAVA)
/* Generated */     if( !outReal )
/* Generated */        return ENUM_VALUE(RetCode,TA_BAD_PARAM,BadParam);
/* Generated */     #endif 
/* Generated */  #endif 
/* Generated */    VALUE_HANDLE_DEREF_TO_ZERO(outNBElement);
/* Generated */    VALUE_HANDLE_DEREF_TO_ZERO(outBegIdx);
/* Generated */    lookbackEMA = LOOKBACK_CALL(EMA)( optInTimePeriod );
/* Generated */    lookbackTotal = lookbackEMA * 3;
/* Generated */    if( startIdx < lookbackTotal )
/* Generated */       startIdx = lookbackTotal;
/* Generated */    if( startIdx > endIdx )
/* Generated */       return ENUM_VALUE(RetCode,TA_SUCCESS,Success); 
/* Generated */    tempInt = lookbackTotal+(endIdx-startIdx)+1;
/* Generated */    ARRAY_ALLOC(firstEMA,tempInt);
/* Generated */    #if !defined( _JAVA )
/* Generated */       if( !firstEMA )
/* Generated */          return ENUM_VALUE(RetCode,TA_ALLOC_ERR,AllocErr);
/* Generated */    #endif
/* Generated */    k = PER_TO_K(optInTimePeriod);
/* Generated */    retCode = FUNCTION_CALL(INT_EMA)( startIdx-(lookbackEMA*2), endIdx, inReal,
/* Generated */                                      optInTimePeriod, k,
/* Generated */                                      VALUE_HANDLE_OUT(firstEMABegIdx), VALUE_HANDLE_OUT(firstEMANbElement),
/* Generated */                      firstEMA );
/* Generated */    if( (retCode != ENUM_VALUE(RetCode,TA_SUCCESS,Success) ) || (VALUE_HANDLE_GET(firstEMANbElement) == 0) )
/* Generated */    {
/* Generated */       ARRAY_FREE( firstEMA );
/* Generated */       return retCode;
/* Generated */    }
/* Generated */    ARRAY_ALLOC(secondEMA,VALUE_HANDLE_GET(firstEMANbElement));
/* Generated */    #if !defined( _JAVA ) && !defined( USE_SUBARRAY )
/* Generated */       if( !secondEMA )
/* Generated */       {
/* Generated */          ARRAY_FREE( firstEMA );
/* Generated */          return ENUM_VALUE(RetCode,TA_ALLOC_ERR,AllocErr);
/* Generated */       }   
/* Generated */    #endif
/* Generated */    retCode = FUNCTION_CALL_DOUBLE(INT_EMA)( 0, VALUE_HANDLE_GET(firstEMANbElement)-1, firstEMA,
/* Generated */                                             optInTimePeriod, k,
/* Generated */                                             VALUE_HANDLE_OUT(secondEMABegIdx), VALUE_HANDLE_OUT(secondEMANbElement), 
/* Generated */                                 secondEMA );
/* Generated */    if( (retCode != ENUM_VALUE(RetCode,TA_SUCCESS,Success) ) || (VALUE_HANDLE_GET(secondEMANbElement) == 0) )      
/* Generated */    {
/* Generated */       ARRAY_FREE( firstEMA );
/* Generated */       ARRAY_FREE( secondEMA );
/* Generated */       return retCode;
/* Generated */    }
/* Generated */    retCode = FUNCTION_CALL_DOUBLE(INT_EMA)( 0, VALUE_HANDLE_GET(secondEMANbElement)-1, secondEMA,
/* Generated */                                             optInTimePeriod, k,
/* Generated */                                             VALUE_HANDLE_OUT(thirdEMABegIdx), VALUE_HANDLE_OUT(thirdEMANbElement),
/* Generated */                                             outReal );
/* Generated */    if( (retCode != ENUM_VALUE(RetCode,TA_SUCCESS,Success) ) || (VALUE_HANDLE_GET(thirdEMANbElement) == 0) )
/* Generated */    {
/* Generated */       ARRAY_FREE( firstEMA );
/* Generated */       ARRAY_FREE( secondEMA );
/* Generated */       return retCode;
/* Generated */    }
/* Generated */    firstEMAIdx  = VALUE_HANDLE_GET(thirdEMABegIdx) + VALUE_HANDLE_GET(secondEMABegIdx);
/* Generated */    secondEMAIdx = VALUE_HANDLE_GET(thirdEMABegIdx);
/* Generated */    VALUE_HANDLE_DEREF(outBegIdx) = firstEMAIdx + VALUE_HANDLE_GET(firstEMABegIdx);
/* Generated */    outIdx = 0;
/* Generated */    while( outIdx < VALUE_HANDLE_GET(thirdEMANbElement) ) 
/* Generated */    {
/* Generated */       outReal[outIdx] += (3.0*firstEMA[firstEMAIdx++]) - (3.0*secondEMA[secondEMAIdx++]);
/* Generated */       outIdx++;
/* Generated */    }
/* Generated */    ARRAY_FREE( firstEMA );
/* Generated */    ARRAY_FREE( secondEMA );
/* Generated */    VALUE_HANDLE_DEREF(outNBElement) = outIdx;
/* Generated */    return ENUM_VALUE(RetCode,TA_SUCCESS,Success);
/* Generated */ }
/* Generated */ 
/* Generated */ #if defined( _MANAGED )
/* Generated */ }}} // Close namespace TicTacTec.TA.Lib
/* Generated */ #endif
/**** END GENCODE SECTION 5 - DO NOT DELETE THIS LINE ****/

