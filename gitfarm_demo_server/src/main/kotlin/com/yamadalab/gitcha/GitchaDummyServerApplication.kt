package com.yamadalab.gitcha

import org.springframework.boot.autoconfigure.SpringBootApplication
import org.springframework.boot.runApplication

@SpringBootApplication
class GitchaDummyServerApplication

fun main(args: Array<String>) {
	runApplication<GitchaDummyServerApplication>(*args)
}
