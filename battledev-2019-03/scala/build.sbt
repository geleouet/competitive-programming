lazy val root = (project in file("."))
	.settings(
		name := "Meritis Blog - BattleDev de Mars 2019 en Scala",
		libraryDependencies += "org.scalatest" %% "scalatest" % "3.0.5" % "test"
	)
