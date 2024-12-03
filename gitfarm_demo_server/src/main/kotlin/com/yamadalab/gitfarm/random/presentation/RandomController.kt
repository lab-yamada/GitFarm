package com.yamadalab.gitfarm.random.presentation

import com.yamadalab.gitfarm.random.application.RandomService
import lombok.AllArgsConstructor
import lombok.RequiredArgsConstructor
import org.springframework.http.ResponseEntity
import org.springframework.web.bind.annotation.GetMapping
import org.springframework.web.bind.annotation.PostMapping
import org.springframework.web.bind.annotation.RestController

@RestController
@RequiredArgsConstructor
@AllArgsConstructor
class RandomController(private val randomService: RandomService) {

    @GetMapping("/draw")
    fun draw(): ResponseEntity<String> {
        val drawResult: String = randomService.draw();
        return ResponseEntity.ok().body(drawResult);
    }

    @PostMapping("/curl")
    fun curl(): ResponseEntity<String> {
        return ResponseEntity.ok().body("hi");
    }
}