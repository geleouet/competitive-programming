package org.meritis.battledev.exo1

import scala.collection.mutable.ListBuffer
import org.scalatest.FunSuite
import scala.io.Source

class RunExerciseTest extends FunSuite {

    class RunExerciseMock(lines: List[String]) extends RunExercise {
        val mockBuffer = new ListBuffer[String]()

        override def input = lines
        override def output(result: String) = (mockBuffer += result)

        def hasResult = !mockBuffer.isEmpty
        def testResult = mockBuffer.head
    }

    test("Exo 1 : Test expecting KO result") {
        val lines = Source.fromURL(getClass.getResource("/exo1_input_ko.txt")).getLines.toList
        val exo = new RunExerciseMock(lines)
        exo.contestResponse()
        if (!exo.hasResult) fail("no result returned")
        else assert(exo.testResult === "KO")
    }

    test("Exo 1 : Test expecting 100") {
        val lines = Source.fromURL(getClass.getResource("/exo1_input_100.txt")).getLines.toList
        val exo = new RunExerciseMock(lines)
        exo.contestResponse()
        if (!exo.hasResult) fail("no result returned")
        else assert(exo.testResult.toInt === 100)
    }

    test("Exo 1 : Test expecting 1000") {
        val lines = Source.fromURL(getClass.getResource("/exo1_input_1000.txt")).getLines.toList
        val exo = new RunExerciseMock(lines)
        exo.contestResponse()
        if (!exo.hasResult) fail("no result returned")
        else assert(exo.testResult.toInt === 1000)
    }

}
