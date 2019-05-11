package org.meritis.battledev.exo5

import scala.collection.mutable.ListBuffer
import org.scalatest.FunSuite

class RunExerciseTest extends FunSuite {

    class RunExerciseMock(corridor: String) extends RunExercise {
        val mockBuffer = new ListBuffer[String]()

        override def input = List(corridor.length.toString, corridor)
        override def output(result: String) = (mockBuffer += result)

        def hasResult = !mockBuffer.isEmpty
        def testResult = mockBuffer.head
    }

    test("Exo 5 : Test with only right corridor") {
        val corridor = "X*o*oo**"
        val exo = new RunExerciseMock(corridor)
        exo.contestResponse()
        if (!exo.hasResult) fail("no result returned")
        else assert(exo.testResult === "*o*oo**")
    }

    test("Exo 5 : Test with only left corridor") {
        val corridor = "o*oooooX"
        val exo = new RunExerciseMock(corridor)
        exo.contestResponse()
        if (!exo.hasResult) fail("no result returned")
        else assert(exo.testResult === "ooooo*o")
    }

    test("Exo 5 : Test with a small corridor") {
        val corridor = "o*oooooX*o*oo**"
        val exo = new RunExerciseMock(corridor)
        exo.contestResponse()
        if (!exo.hasResult) fail("no result returned")
        else assert(exo.testResult === "ooooo*o*oo*o**")
    }

    test("Exo 5 : Test with a large corridor") {
        val corridor = "o*ooo***ooooo*Xo*oooo*o**oo**"
        val exo = new RunExerciseMock(corridor)
        exo.contestResponse()
        if (!exo.hasResult) fail("no result returned")
        else assert(exo.testResult === "o*ooooo*oooo*o**oo***ooo*o**")
    }

}
