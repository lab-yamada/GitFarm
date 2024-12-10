package com.yamadalab.gitfarm.middleware.utils;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory;
import com.fasterxml.jackson.module.kotlin.KotlinModule;
import com.fasterxml.jackson.module.kotlin.readValue;
import kotlinx.io.files.FileNotFoundException;
import java.io.File;

class Utils {

    companion object {
        private const val RESOURCE_PATH: String = "src/main/resources";

        fun loadSharedLibrary(fileName: String): Unit {
            val cppLibName: String = System.mapLibraryName(fileName);
            val cppLibFile: File = File("$RESOURCE_PATH/libs/$cppLibName");
            println("cppLibFile : ${cppLibFile.absolutePath}");
            System.load(cppLibFile.absolutePath);
        }

        fun loadGraphQL(fileName: String): String {
            val qlFile: File = File("$RESOURCE_PATH/graphql/$fileName");
            if (!qlFile.exists()) {
                throw FileNotFoundException("GraphQL File Not Found: $fileName");
            }
            return qlFile.readText(Charsets.UTF_8);
        }

        fun loadTokenByYaml(fileName: String): String {
            val mapper: ObjectMapper = ObjectMapper(YAMLFactory()).registerModule(KotlinModule.Builder().build());
            val yamlFile: File = File("$RESOURCE_PATH/yaml/$fileName");
            val yamlData: Map<String, String> = mapper.readValue(yamlFile);
            return yamlData["token"] ?: throw IllegalArgumentException("Token not found in the YAML file.");
        }
    }
}