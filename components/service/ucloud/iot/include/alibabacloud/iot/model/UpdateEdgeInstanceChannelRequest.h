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

#ifndef ALIBABACLOUD_IOT_MODEL_UPDATEEDGEINSTANCECHANNELREQUEST_H_
#define ALIBABACLOUD_IOT_MODEL_UPDATEEDGEINSTANCECHANNELREQUEST_H_

#include <string>
#include <vector>
#include <alibabacloud/core/RpcServiceRequest.h>
#include <alibabacloud/iot/IotExport.h>

namespace AlibabaCloud
{
	namespace Iot
	{
		namespace Model
		{
			class ALIBABACLOUD_IOT_EXPORT UpdateEdgeInstanceChannelRequest : public RpcServiceRequest
			{
			public:
				struct Configs
				{
					std::string format;
					std::string content;
					std::string key;
				};

			public:
				UpdateEdgeInstanceChannelRequest();
				~UpdateEdgeInstanceChannelRequest();

				std::vector<Configs> getConfigs()const;
				void setConfigs(const std::vector<Configs>& configs);
				std::string getAccessKeyId()const;
				void setAccessKeyId(const std::string& accessKeyId);
				std::string getDriverId()const;
				void setDriverId(const std::string& driverId);
				std::string getIotInstanceId()const;
				void setIotInstanceId(const std::string& iotInstanceId);
				std::string getChannelName()const;
				void setChannelName(const std::string& channelName);
				std::string getInstanceId()const;
				void setInstanceId(const std::string& instanceId);
				std::string getApiProduct()const;
				void setApiProduct(const std::string& apiProduct);
				std::string getApiRevision()const;
				void setApiRevision(const std::string& apiRevision);
				std::string getChannelId()const;
				void setChannelId(const std::string& channelId);

            private:
				std::vector<Configs> configs_;
				std::string accessKeyId_;
				std::string driverId_;
				std::string iotInstanceId_;
				std::string channelName_;
				std::string instanceId_;
				std::string apiProduct_;
				std::string apiRevision_;
				std::string channelId_;

			};
		}
	}
}
#endif // !ALIBABACLOUD_IOT_MODEL_UPDATEEDGEINSTANCECHANNELREQUEST_H_