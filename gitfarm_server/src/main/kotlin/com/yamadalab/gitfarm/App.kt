package com.yamadalab.gitfarm

import org.springframework.boot.autoconfigure.SpringBootApplication
import org.springframework.boot.runApplication

@SpringBootApplication
class GitfarmServerApplication

fun main(args: Array<String>) {
    runApplication<GitfarmServerApplication>(*args)
}