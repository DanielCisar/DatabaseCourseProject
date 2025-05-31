#include "FileOpenCommand.hpp"
#include "CommandContext.hpp" 
#include "Catalog.hpp"        
#include "FileUtils.hpp"      
#include <fstream>            
#include <iostream>           
#include <stdexcept>          

/**
 * @brief Constructs a FileOpenCommand object, initializing it with the shared command context.
 *
 * @param context A reference to the `CommandContext` object. This context is
 * vital for the command to interact with the application's
 * global state, including the shared database catalog and
 * all necessary file and console I/O components.
 */
FileOpenCommand::FileOpenCommand(CommandContext& context)
	: context(context) {
}

/**
 * @brief Executes the "open" command, managing the loading or creation of a database catalog.
 *
 * This function validates the command parameters, expecting exactly one argument
 * which is the path to the catalog file.
 * - If the specified file does not exist, an empty file is created at the given path,
 * and a success message is printed to the console.
 * - If the file exists, its content is read using `InputFileReader::readCatalogFromFile`,
 * and the parsed `Catalog` data is deep-copied into the `context.loadedCatalog` object,
 * which represents the application's active catalog.
 * The `context.loadedCatalogExists` flag is set to `true` upon successful operation.
 *
 * @param params A constant reference to a vector of strings containing the command name and its arguments.
 * `params[0]` is "open", and `params[1]` is the file path.
 *
 * @throws std::runtime_error If `params.size()` is not equal to 2, indicating missing arguments.
 * @throws std::runtime_error If there's a failure in creating a new file (e.g., permissions issue).
 * @throws std::exception Any exceptions propagated from `InputFileReader::readCatalogFromFile`
 * during the process of reading and parsing the catalog file.
 */
void FileOpenCommand::execute(const std::vector<std::string>& params) {

	if (params.size() != 2) {
		throw std::runtime_error("Not enough parameters. ");
	}

	const std::string& filepath = params[1];

	if (!FileUtils::fileExists(filepath)) {
		std::ofstream newFile(filepath);
		if (!newFile) {
			throw std::runtime_error("Error creating file at: " + filepath);
		}
		newFile.close();
		context.outputConsoleWritter.printLine("Created new empty file: " + filepath);

	}
	try {
		Catalog catalog = Catalog(context.inputFileReader
			.readCatalogFromFile(filepath));
		context.outputConsoleWritter.printLine("Successfully opened: " + filepath);

		context.loadedCatalog = catalog;
		context.loadedCatalogExists = true;
	}
	catch (const std::exception& e) {
		context.outputConsoleWritter.printLine(e.what());
		return;
	}
}

/**
 * @brief Creates a deep copy of the current `FileOpenCommand` object.
 *
 * This override constructs a new `FileOpenCommand` instance,
 * associating it with the provided `newContext`. Since `FileOpenCommand`
 * itself only holds a reference to `CommandContext` and no other dynamically
 * allocated members, a simple construction with the new context is sufficient
 * for cloning this command object.
 *
 * @param newContext A reference to the `CommandContext` that the new cloned command should use.
 * @return A pointer to a newly allocated `FileOpenCommand` object.
 * @warning The caller is responsible for deleteing the returned pointer.
 */
Command* FileOpenCommand::clone(CommandContext& newContext) const {
	return new FileOpenCommand(newContext);
}