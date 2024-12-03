package com.yamadalab.gitfarm

import org.springframework.boot.autoconfigure.SpringBootApplication
import org.springframework.boot.runApplication

@SpringBootApplication
class GitfarmDummyServerApplication

fun main(args: Array<String>) {
	runApplication<GitfarmDummyServerApplication>(*args)
}
