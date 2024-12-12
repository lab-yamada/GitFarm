package com.yamadalab.gitfarm.middleware.utils;

import com.fasterxml.jackson.databind.ObjectMapper
import com.fasterxml.jackson.dataformat.yaml.YAMLFactory
import com.fasterxml.jackson.module.kotlin.KotlinModule
import com.fasterxml.jackson.module.kotlin.readValue
import kotlinx.io.files.FileNotFoundException
import java.io.File

class Utils {

    companion object {
        private const val RESOURCE_PATH: String = "src/main/resources";
        private const val MIDDLEWARE_NAME: String = "gitfarm_middleware";
        private const val SERVER_NAME: String = "gitfarm_server";

        private fun getPwd(): String {
            val path: String = System.getProperty("user.dir");
            return path;
        }

        private fun getProjectResourcePath(): String {
            val pwd: String = getPwd();
            println("Pwd : ${getPwd()}");

            var projectName: String = "";
            var projectPath: String = "";
            var resourcePath: String = "";

            if (!pwd.contains(MIDDLEWARE_NAME)) {
                projectName = SERVER_NAME;
                projectPath = pwd.replace(SERVER_NAME, MIDDLEWARE_NAME);
                resourcePath = "$projectPath/$RESOURCE_PATH";
            } else {
                projectName = MIDDLEWARE_NAME;
                resourcePath = RESOURCE_PATH;
            }

            if (projectPath.contains("$projectName/build/libs")) {
                projectPath = projectPath.replace("$projectName/build/libs", "");
            }

            println("ProjectPath : $projectPath");
            println("ResourcePath : $resourcePath");

            return resourcePath;
        }

        fun loadSharedLibrary(fileName: String): Unit {
            val cppLibName: String = System.mapLibraryName(fileName);
            val cppLibFile: File = File("${getProjectResourcePath()}/libs/$cppLibName");
            println("cppLibFile : ${cppLibFile.absolutePath}");
            System.load(cppLibFile.absolutePath);
        }

        fun loadGraphQL(fileName: String): String {
            val qlFile: File = File("${getProjectResourcePath()}/graphql/$fileName");
            if (!qlFile.exists()) {
                throw FileNotFoundException("GraphQL File Not Found: $fileName");
            }
            return qlFile.readText(Charsets.UTF_8);
        }

        fun loadTokenByYaml(fileName: String): String {
            val mapper: ObjectMapper = ObjectMapper(YAMLFactory()).registerModule(KotlinModule.Builder().build());
            val yamlFile: File = File("${getProjectResourcePath()}/yaml/$fileName");
            val yamlData: Map<String, String> = mapper.readValue(yamlFile);
            return yamlData["token"] ?: throw IllegalArgumentException("Token not found in the YAML file.");
        }
    }
}