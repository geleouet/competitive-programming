package org.meritis.battledev.exo2

import scala.collection.mutable.ListBuffer
import org.scalatest.FunSuite

class RunExerciseTest extends FunSuite {

    class RunExerciseMock(weights: List[Int]) extends RunExercise {
        val mockBuffer = new ListBuffer[Int]()

        override def input = weights.size.toString :: weights.map(_.toString)
        override def output(result: Int) = (mockBuffer += result)

        def hasResult = !mockBuffer.isEmpty
        def testResult = mockBuffer.head
    }

    test("Exo 2 : Test with 7 elements") {
        val weights = List(25, 53, 51, 68, 69, 21, 54)
        val exo = new RunExerciseMock(weights)
        exo.contestResponse()
        if (!exo.hasResult) fail("no result returned")
        else assert(exo.testResult === 5)
    }

    test("Exo 2 : Test with 58 elements") {
        val weights = List(25, 53, 51, 68, 69, 21, 54, 68, 42, 8, 55, 32, 63, 45, 54, 37, 7, 21, 17, 2, 41, 55, 57, 62, 37, 42, 4, 38, 22, 67, 41, 31, 52, 54, 48, 35, 43, 42, 20, 45, 39, 58, 30, 23, 42, 62, 48, 61, 45, 45, 44, 48, 1, 9, 13, 41, 64, 20)
        val exo = new RunExerciseMock(weights)
        exo.contestResponse()
        if (!exo.hasResult) fail("no result returned")
        else assert(exo.testResult === 31)
    }

}
