/*
 * This software was developed at the National Institute of Standards and
 * Technology (NIST) by employees of the Federal Government in the course
 * of their official duties. Pursuant to title 17 Section 105 of the
 * United States Code, this software is not subject to copyright protection
 * and is in the public domain. NIST assumes no responsibility whatsoever for
 * its use by other parties, and makes no guarantees, expressed or implied,
 * about its quality, reliability, or any other characteristic.
 */

#ifndef __BE_PROCESS_WORKERCONTROLLER_H__
#define __BE_PROCESS_WORKERCONTROLLER_H__

#include <tr1/memory>

#include <be_error_exception.h>
#include <be_process.h>
#include <be_process_worker.h>

using namespace std;

namespace BiometricEvaluation
{
	namespace Process
	{
		/**
		 * @brief
		 * Wrapper of a Worker returned from a Process::Manager
		 */
		class WorkerController
		{
		public:
			/**
			 * WorkerController constructor.
			 *
			 * @param worker
			 *	The Worker instance to wrap.
			 */
			WorkerController(
			    tr1::shared_ptr<Worker> worker);
		
			/**
			 * @brief
			 * Set the parameter to be passed to the Worker.
			 *
			 * @param name[in]
			 *	The name representing the argument in the
			 *	Worker.
			 * @param argument[in]
			 *	The argument to be passed to the Worker.
			 *
			 * @note
			 *	Subsequent calls to setParameter() with the 
			 *	same name will overwrite any exiting argument.
			 */
			virtual void
			setParameter(
			    const string &name, 
			    tr1::shared_ptr<void> argument);
			    
			/**
			 * @brief
			 * Reuse the Worker.
			 *
			 * @throw Error::ObjectExists
			 *	The previously started Worker is still
			 *	running.
			 */
			virtual void
			reset()
			    throw (Error::ObjectExists);
			
			/**
			 * @brief
			 * Obtain whether or not Worker is working.
			 *
			 * @return
			 *	Whether or not the Worker is working.
			 */
			virtual bool
			isWorking()
			    const = 0;
			
			/**
			 * @brief
			 * Obtain the Worker instance being wrapped.
			 *
			 * @return
			 *	Worker instance.
			 */
			tr1::shared_ptr<Worker>
			getWorker()
			    const;
			
			/**
			 * @brief
			 * WorkerController destructor.
			 */
			virtual ~WorkerController();

		protected:
			/** The Worker instance that is running in this child */
			tr1::shared_ptr<Worker> _worker;
		
		private:
			/**
			 * @brief
			 * Start the Worker decorated by this instance.
			 *
			 * @throw Error::ObjectExists
			 *	The decorated Worker is already working.
			 * @throw Error::StrategyError
			 *	Error in starting Worker.
			 *
			 * @note
			 *	Method is private so that it can only be
			 *	called from a friend Process::Manager.
			 */
			virtual void
			start()
			    throw (Error::ObjectExists,
			    Error::StrategyError) = 0;
			    
			/**
			 * @brief
			 * Tell the Worker to stop.
			 *
			 * @return
			 *	Return code from Worker.
			 *
			 * @throw Error::ObjectDoesNotExist
			 *	Worker is not working.
			 * @throw Error::StrategyError
			 *	Error asking Worker to stop.
			 */
			virtual int32_t
			stop()
			    throw (Error::ObjectDoesNotExist,
			    Error::StrategyError) = 0;
		};
	}
}

#endif /* __BE_PROCESS_WORKERCONTROLLER_H__ */