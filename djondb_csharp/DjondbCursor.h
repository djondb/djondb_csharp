#pragma once
#include "djondb_client.h"
#include "BSONObj.h"

namespace Djondb {
	public ref class DjondbCursor
	{
	public:
		DjondbCursor(djondb::DjondbCursor* cursor);
		virtual ~DjondbCursor(void);

		/**
		* @brief checks if more elements could be retrieved
		*
		* @return true if more BSONObj are ready, false otherwise
		*/
		bool next();
		/**
		* @brief checks if there are elements in the front of the cursor
		*
		* @return true of not BOF, false otherwise
		*/
		bool previous();
		/**
		* @brief Returns the current loaded element, the client should call next() method before calling this, if not
		* an unexpected behavior could occur
		*
		* @return the current element or NULL if the next method was not called
		*/
		BSONObj^ current();

		/**
		* @brief This will retrieve the length of the rows contained in the cursor, if the cursor is still loading then
		* all the rows will be retrieved from the server. This method should be used with care, because it will try to
		* retrieve every row from the server and it may contain several pages
		*
		* @return length of the cursor
		*/
		__int32 length();

		/**
		* @brief Releases the cursor from the server, the client should use this method if the cursor is no longer required
		*/
		void releaseCursor();

		/**
		* @brief Will place the current row in the desired position
		*
		* @param position
		*/
		void seek(__int32 position);

		djondb::DjondbCursor* ptr();

	private:
		djondb::DjondbCursor* _internal;
		Djondb::BSONObj^ _current;
	};

};
