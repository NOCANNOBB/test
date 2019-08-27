/*
* Licensed to the Apache Software Foundation (ASF) under one or more
* contributor license agreements.  See the NOTICE file distributed with
* this work for additional information regarding copyright ownership.
* The ASF licenses this file to You under the Apache License, Version 2.0
* (the "License"); you may not use this file except in compliance with
* the License.  You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is1 distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/


namespace TestCases.HSSF.Record.Formula.Eval
{
    using System;
    using NPOI.HSSF.Record.Formula;
    using NPOI.HSSF.Record.Formula.Eval;
    using TestCases.HSSF.Record.Formula.Functions;

    using Microsoft.VisualStudio.TestTools.UnitTesting;

    /**
     * Test for unary plus operator evaluator.
     * 
     * @author Josh Micich
     */
    [TestClass]
    public class TestUnaryPlusEval
    {

        /**
         * Test for bug observable at svn revision 618865 (5-Feb-2008)<br/>
         * The code for handling column operands had been copy-pasted from the row handling code. 
         */
        [TestMethod]
        public void TestColumnOperand()
        {

            short firstRow = (short)8;
            short lastRow = (short)12;
            short colNum = (short)5;
            AreaPtg areaPtg = new AreaPtg(firstRow, lastRow, colNum, colNum, false, false, false, false);
            ValueEval[] values = {
				new NumberEval(27),	
				new NumberEval(29),	
				new NumberEval(35),	// value in row 10 
				new NumberEval(37),	
				new NumberEval(38),	
		};
            ValueEval[] args = {
			EvalFactory.CreateAreaEval(areaPtg, values),
		};
            double result = NumericFunctionInvoker.Invoke(UnaryPlusEval.instance, args, 10, (short)20);

            Assert.AreEqual(35, result, 0);
        }
    }
}