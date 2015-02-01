#pragma once
#include "djondb_client.h"

typedef BSONArrayObj I_BSONArrayObj;

namespace Djondb {
	ref class BSONObj;

	generic <class T>
	public ref class BSONArrayObj: System::Collections::Generic::IEnumerable<T>
	{
	public:
		BSONArrayObj();
		BSONArrayObj(I_BSONArrayObj* arr);
		virtual ~BSONArrayObj();

		virtual __int32 length();
		/**
		* @brief Adds the BSONObj to the array
		*
		* @param obj
		*/
		void add(Djondb::BSONObj^ obj);
		/**
		* @brief Adds all the elements of the argument to the current elements
		*
		* @param array
		*/
		void addAll(BSONArrayObj<T>^ arr);
		virtual BSONObj^ get(__int32 index);
		virtual System::String^ toChar();
		virtual BSONArrayObj^ select(System::String^ select);

		I_BSONArrayObj* ptr() {
			return _internal;
		}

		ref struct BSONArrayEnumerator : System::Collections::Generic::IEnumerator<T>
		{
			BSONArrayObj^ _instance;
			int _index;

			BSONArrayEnumerator( BSONArrayObj^ arr )

			{
				_index = -1;
			}

			BSONArrayEnumerator( BSONArrayEnumerator^ en )
			{
			}

			virtual bool MoveNext() = System::Collections::Generic::IEnumerator<T>::MoveNext
			{
				if( _index < _instance->length() )
				{
					_index++;
					return true;
				}
				return false;
			}

			property T Current
			{
				virtual T get() = System::Collections::Generic::IEnumerator<T>::Current::get
				{
					return (T)_instance->get(_index);
				}
			};
			// This is required as IEnumerator<T> also implements IEnumerator
			property System::Object^ Current2
			{
				virtual System::Object^ get() = System::Collections::IEnumerator::Current::get
				{
					return (T)_instance->get(_index);
				}
			};

			virtual void Reset() = System::Collections::Generic::IEnumerator<T>::Reset {
				_index = -1;
			}

			~BSONArrayEnumerator() {}
		};

		virtual System::Collections::Generic::IEnumerator<T>^ GetEnumerator()
		{
			return gcnew BSONArrayEnumerator(this);
		}

		virtual System::Collections::IEnumerator^ GetEnumerator2() = System::Collections::IEnumerable::GetEnumerator
		{
			return gcnew BSONArrayEnumerator(this);
		}

	private:
		I_BSONArrayObj* _internal;
	};

};