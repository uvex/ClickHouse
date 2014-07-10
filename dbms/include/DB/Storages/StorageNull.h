#pragma once

#include <DB/Core/NamesAndTypes.h>
#include <DB/Storages/IStorage.h>
#include <DB/DataStreams/NullBlockInputStream.h>
#include <DB/DataStreams/NullBlockOutputStream.h>


namespace DB
{

/** При записи, ничего не делает.
  * При чтении, возвращает пустоту.
  */
class StorageNull : public IStorage
{
public:
	static StoragePtr create(const std::string & name_, NamesAndTypesListPtr columns_)
	{
		return (new StorageNull(name_, columns_))->thisPtr();
	}

	std::string getName() const { return "Null"; }
	std::string getTableName() const { return name; }

	const NamesAndTypesList & getColumnsList() const { return *columns; }

	BlockInputStreams read(
		const Names & column_names,
		ASTPtr query,
		const Settings & settings,
		QueryProcessingStage::Enum & processed_stage,
		size_t max_block_size = DEFAULT_BLOCK_SIZE,
		unsigned threads = 1)
	{
		return { new NullBlockInputStream };
	}

	BlockOutputStreamPtr write(
		ASTPtr query)
	{
		return new NullBlockOutputStream;
	}

	void rename(const String & new_path_to_db, const String & new_name) { name = new_name; }

private:
	String name;
	NamesAndTypesListPtr columns;

    StorageNull(const std::string & name_, NamesAndTypesListPtr columns_)
		: name(name_), columns(columns_) {}
};

}