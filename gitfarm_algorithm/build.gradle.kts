plugins {
    kotlin("jvm") version "2.0.21"
}

group = "com.yamadalab.gitfarm"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
}

dependencies {
    implementation(kotlin("stdlib"))
}

tasks.jar {
    manifest {
        attributes["Main-Class"] = "MainKt"
    }

    duplicatesStrategy = DuplicatesStrategy.EXCLUDE

    from(sourceSets.main.get().output)

    dependsOn(configurations.runtimeClasspath)
    from({
        configurations.runtimeClasspath.get().filter { it.name.endsWith("jar") }.map { zipTree(it) }
    })
}

tasks.test {
    useJUnitPlatform()
}

kotlin {
    jvmToolchain(17)
}
