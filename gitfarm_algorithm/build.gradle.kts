plugins {
    kotlin("jvm") version "2.0.21"
    application
}

group = "com.yamadalab.gitfarm"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
}

dependencies {
    testImplementation(kotlin("test"))
}

tasks.test {
    useJUnitPlatform()
}

kotlin {
    jvmToolchain(17)
}

application {
    mainClass.set("com.yamadalab.gitfarm.Main")
}