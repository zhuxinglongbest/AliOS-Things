/*
 * Copyright 2009-2017 Alibaba Cloud All rights reserved.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ALIBABACLOUD_VISIONAI_POC_MODEL_RECOGNIZECARRESULT_H_
#define ALIBABACLOUD_VISIONAI_POC_MODEL_RECOGNIZECARRESULT_H_

#include <string>
#include <vector>
#include <utility>
#include <alibabacloud/core/ServiceResult.h>
#include <alibabacloud/visionai-poc/Visionai_pocExport.h>

namespace AlibabaCloud
{
	namespace Visionai_poc
	{
		namespace Model
		{
			class ALIBABACLOUD_VISIONAI_POC_EXPORT RecognizeCarResult : public ServiceResult
			{
			public:
				struct Response
				{
					struct Data
					{
						std::string modelName;
						std::string description;
						std::string sptId;
						std::string confidence;
						std::string prop;
						std::string external;
						std::string picUrl;
						std::string roid;
						std::string name;
						std::string tips;
						std::string predictRes;
					};
					std::string requestId;
					Data data;
					std::string errorCode;
					std::string errorMessage;
					bool success;
					std::string url;
				};


				RecognizeCarResult();
				explicit RecognizeCarResult(const std::string &payload);
				~RecognizeCarResult();
				Response getResponse()const;
				std::string getMessage()const;
				int getCode()const;
				bool getSuccess()const;

			protected:
				void parse(const std::string &payload);
			private:
				Response response_;
				std::string message_;
				int code_;
				bool success_;

			};
		}
	}
}
#endif // !ALIBABACLOUD_VISIONAI_POC_MODEL_RECOGNIZECARRESULT_H_