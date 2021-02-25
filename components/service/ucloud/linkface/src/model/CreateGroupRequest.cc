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

#include <alibabacloud/linkface/model/CreateGroupRequest.h>

using AlibabaCloud::LinkFace::Model::CreateGroupRequest;

CreateGroupRequest::CreateGroupRequest() :
	RpcServiceRequest("linkface", "2018-07-20", "CreateGroup")
{
	setMethod(HttpRequest::Method::Post);
}

CreateGroupRequest::~CreateGroupRequest()
{}

std::string CreateGroupRequest::getGroupId()const
{
	return groupId_;
}

void CreateGroupRequest::setGroupId(const std::string& groupId)
{
	groupId_ = groupId;
	setBodyParameter("GroupId", groupId);
}

std::string CreateGroupRequest::getApiProduct()const
{
	return apiProduct_;
}

void CreateGroupRequest::setApiProduct(const std::string& apiProduct)
{
	apiProduct_ = apiProduct;
	setBodyParameter("ApiProduct", apiProduct);
}

std::string CreateGroupRequest::getApiRevision()const
{
	return apiRevision_;
}

void CreateGroupRequest::setApiRevision(const std::string& apiRevision)
{
	apiRevision_ = apiRevision;
	setBodyParameter("ApiRevision", apiRevision);
}

