/******************************************************************************
 * This software was developed at the National Institute of Standards and
 * Technology (NIST) by employees of the Federal Government in the course
 * of their official duties. Pursuant to title 17 Section 105 of the
 * United States Code, this software is not subject to copyright protection
 * and is in the public domain. NIST assumes no responsibility whatsoever for
 * its use by other parties, and makes no guarantees, expressed or implied,
 * about its quality, reliability, or any other characteristic.
 ******************************************************************************/
#ifndef __BE_FILERECSTORE_H__
#define __BE_FILERECSTORE_H__

#include <string>
#include <vector>
#include <be_recordstore.h>
using namespace std;

/*
 * This file contains the class declaration for an implementation of a
 * RecordStore using a on-disk database.
 */
namespace BiometricEvaluation {

	/*
	 * Class to represent the data storage mechanism.
	 */
	class FileRecordStore : public RecordStore {
		public:
			
			/*
			 * Construct a new File record store.
			 */
			FileRecordStore(
			    const string &name,
			    const string &description)
			    throw (ObjectExists, StrategyError);

			/*
			 * Open an existing File record store.
			 */
			FileRecordStore(
			    const string &name)
			    throw (ObjectDoesNotExist, StrategyError);

			void insert(
			    const string &key,
			    const void *data,
			    const uint64_t size)
			    throw (ObjectExists, StrategyError);

			void remove(
			    const string &key)
			    throw (ObjectDoesNotExist, StrategyError);

			uint64_t read(
			    const string &key,
			    void * data)
			    throw (ParameterError, StrategyError);

			virtual void replace(
			    const string &key,
			    void * data)
			    throw (ParameterError, StrategyError);

			void flush(
			    const string &key)
			    throw (ParameterError, StrategyError);

		protected:

		private:
			string _directory;
			string canonicalName(const string &name);
			bool fileExists(const string &name);
			void readControlFile() throw (StrategyError);
			void writeControlFile() throw (StrategyError);
			uint64_t getObjSize(const string &name)
			    throw (ObjectDoesNotExist, StrategyError);

	};
}
#endif	/* __BE_FILERECSTORE_H__ */
