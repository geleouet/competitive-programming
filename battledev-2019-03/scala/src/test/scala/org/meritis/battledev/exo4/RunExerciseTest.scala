package org.meritis.battledev.exo4

import scala.collection.mutable.ListBuffer
import org.scalatest.FunSuite
import scala.io.Source

class RunExerciseTest extends FunSuite {

    class RunExerciseMock(words: List[String]) extends RunExercise {
        val mockBuffer = new ListBuffer[String]()

        override def input = words.size.toString :: words
        override def output(result: String) = (mockBuffer += result)

        def hasResult = !mockBuffer.isEmpty
        def testResult = mockBuffer.head
    }

    test("Exo 4 : Test with 3 words") {
        val words = List("artificiel", "algorithme", "algebrique")
        val exo = new RunExerciseMock(words)
        exo.contestResponse()
        if (!exo.hasResult) fail("no result returned")
        else assert(exo.testResult === "arie")
    }

    test("Exo 4 : Test with 20 words") {
        val words = List("zyyyzzxxxx", "zyzyzzxzxx", "yzyzxzxxxx", "yzzxzxzxxx", "yxxzzzyxxx", "xyxxyzyzxx", "yyyxxyxzxx", "zzyyyzyzxx", "xzxzyzxyxx", "yyxyyyyyxx", "zyzyxxzxxx", "zyxyxyzxxx", "zzyxxyzyxx", "xzxzxxyyxx", "zzxyxyxyxx", "yzzyxxxzxx", "yxxzzzzyxx", "xyxzxyzxxx", "xxzyyxzzxx", "yyxxyzxzxx")
        val exo = new RunExerciseMock(words)
        exo.contestResponse()
        if (!exo.hasResult) fail("no result returned")
        else assert(exo.testResult === "yxx")
    }

}
