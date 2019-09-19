/*
 * Copyright (C) 2010-2018 Arm Limited or its affiliates. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdint.h>
#include <stdio.h>
#include "arm_math.h"
#include "cifar10_weights.h"

#define IMG_DATA_CAT {158, 112, 49, 159, 111, 47, 165, 116, 51, 166, 118, 53, 160, 112, 46, 156, 109, 41, 162, 115, 47, 159, 113, 45, 158, 111, 44, 159, 113, 41, 161, 116, 41, 160, 111, 52, 161, 111, 49, 166, 117, 41, 169, 117, 45, 170, 119, 44, 167, 117, 40, 162, 113, 38, 160, 111, 39, 160, 112, 43, 156, 109, 44, 149, 107, 45, 150, 107, 45, 148, 106, 43, 149, 107, 44, 143, 101, 39, 140, 98, 43, 141, 97, 41, 143, 97, 38, 137, 95, 36, 126, 91, 36, 116, 85, 33, 152, 112, 51, 151, 110, 40, 159, 114, 45, 166, 116, 56, 162, 112, 49, 160, 113, 43, 164, 117, 47, 162, 114, 45, 163, 116, 46, 156, 110, 38, 155, 111, 41, 159, 110, 54, 163, 113, 52, 170, 119, 41, 171, 117, 40, 171, 115, 33, 169, 115, 30, 160, 111, 33, 154, 112, 41, 151, 115, 50, 145, 110, 53, 139, 104, 55, 140, 102, 52, 141, 100, 48, 149, 105, 50, 147, 102, 46, 145, 102, 45, 142, 97, 38, 143, 98, 34, 136, 95, 31, 125, 91, 32, 119, 88, 34, 151, 110, 47, 151, 109, 33, 158, 111, 36, 167, 111, 48, 160, 106, 42, 163, 115, 44, 165, 117, 45, 165, 117, 45, 163, 115, 43, 162, 115, 43, 158, 114, 48, 157, 109, 57, 161, 111, 51, 166, 115, 38, 167, 114, 37, 169, 113, 35, 170, 116, 39, 159, 114, 47, 145, 111, 54, 121, 96, 49, 110, 90, 52, 98, 78, 50, 101, 77, 47, 114, 85, 50, 120, 86, 48, 134, 96, 55, 143, 103, 51, 140, 99, 39, 142, 99, 35, 139, 98, 34, 130, 95, 34, 120, 89, 33, 155, 107, 40, 155, 110, 32, 160, 109, 31, 174, 112, 44, 167, 110, 43, 167, 117, 46, 169, 120, 48, 169, 119, 48, 165, 115, 44, 165, 117, 45, 167, 123, 57, 191, 146, 95, 177, 130, 75, 157, 111, 41, 162, 115, 47, 164, 114, 54, 158, 112, 58, 149, 111, 67, 104, 80, 47, 103, 87, 65, 98, 90, 76, 92, 90, 84, 80, 75, 66, 74, 63, 50, 86, 70, 52, 83, 62, 39, 113, 85, 45, 132, 98, 46, 140, 102, 43, 140, 101, 39, 136, 99, 39, 127, 94, 36, 155, 107, 41, 156, 114, 48, 161, 115, 49, 170, 114, 47, 169, 114, 43, 163, 113, 40, 169, 120, 47, 166, 116, 44, 164, 113, 41, 164, 116, 42, 173, 128, 59, 246, 214, 164, 195, 156, 107, 151, 114, 56, 146, 111, 60, 142, 108, 71, 111, 80, 50, 78, 53, 31, 85, 69, 56, 113, 103, 98, 112, 110, 111, 106, 114, 118, 97, 102, 105, 93, 94, 93, 74, 72, 67, 84, 78, 70, 85, 73, 47, 105, 83, 45, 128, 96, 48, 138, 101, 46, 133, 94, 36, 129, 93, 36, 148, 109, 54, 133, 104, 64, 130, 100, 57, 147, 112, 53, 161, 115, 44, 165, 113, 39, 167, 116, 41, 167, 115, 41, 163, 111, 37, 165, 116, 39, 163, 118, 42, 180, 138, 85, 157, 122, 78, 128, 102, 58, 97, 75, 43, 66, 50, 31, 69, 58, 43, 66, 56, 45, 89, 83, 76, 118, 113, 110, 122, 121, 120, 119, 122, 122, 114, 116, 116, 94, 96, 96, 99, 100, 97, 91, 91, 86, 58, 58, 47, 67, 58, 37, 108, 84, 49, 140, 105, 58, 138, 98, 44, 134, 95, 40, 127, 100, 57, 109, 95, 80, 47, 37, 17, 88, 74, 28, 153, 117, 48, 170, 118, 43, 168, 115, 40, 170, 118, 43, 169, 117, 42, 166, 116, 37, 164, 120, 39, 147, 107, 52, 129, 98, 59, 127, 108, 75, 100, 87, 70, 68, 67, 57, 78, 83, 72, 72, 75, 64, 83, 84, 74, 132, 130, 121, 146, 142, 132, 124, 118, 108, 105, 99, 90, 107, 102, 94, 115, 111, 103, 85, 83, 77, 63, 71, 69, 46, 47, 39, 79, 61, 36, 132, 98, 58, 141, 99, 48, 134, 93, 39, 131, 115, 90, 99, 96, 92, 42, 43, 38, 70, 64, 41, 143, 111, 56, 167, 117, 42, 165, 114, 36, 168, 116, 39, 171, 119, 49, 161, 113, 51, 140, 109, 51, 120, 94, 49, 130, 110, 77, 144, 131, 107, 116, 106, 93, 88, 87, 79, 91, 95, 88, 85, 88, 82, 77, 77, 69, 124, 118, 107, 163, 153, 140, 136, 124, 112, 102, 93, 81, 106, 98, 88, 100, 93, 84, 85, 81, 74, 54, 60, 58, 49, 53, 49, 57, 47, 32, 107, 83, 50, 138, 103, 51, 136, 97, 39, 170, 161, 144, 103, 105, 105, 54, 58, 59, 124, 121, 113, 153, 124, 82, 161, 113, 43, 163, 117, 41, 166, 122, 50, 165, 121, 66, 174, 135, 95, 113, 89, 59, 125, 105, 78, 157, 141, 121, 156, 143, 128, 121, 111, 101, 86, 80, 74, 82, 81, 77, 84, 85, 82, 80, 78, 73, 81, 71, 61, 138, 125, 112, 146, 135, 123, 113, 103, 93, 87, 79, 70, 83, 77, 69, 86, 82, 76, 71, 73, 67, 56, 57, 53, 40, 35, 27, 74, 59, 35, 133, 106, 59, 137, 103, 45, 180, 176, 163, 134, 139, 143, 94, 100, 105, 154, 154, 149, 174, 149, 112, 158, 116, 51, 156, 116, 47, 153, 118, 60, 207, 180, 146, 237, 214, 198, 207, 180, 166, 156, 131, 119, 174, 153, 145, 148, 131, 125, 125, 110, 107, 93, 85, 79, 86, 84, 79, 74, 74, 71, 59, 57, 53, 76, 68, 58, 137, 125, 112, 143, 133, 122, 133, 124, 114, 106, 98, 89, 86, 81, 74, 87, 85, 78, 84, 85, 78, 75, 76, 71, 50, 49, 43, 40, 30, 15, 95, 75, 44, 132, 103, 57, 183, 183, 175, 108, 116, 122, 142, 151, 158, 165, 169, 168, 177, 156, 122, 155, 112, 50, 159, 118, 51, 122, 89, 47, 213, 197, 179, 237, 224, 226, 220, 191, 188, 164, 135, 131, 183, 159, 155, 156, 137, 132, 125, 108, 104, 120, 111, 104, 78, 76, 69, 80, 80, 77, 45, 44, 40, 91, 85, 77, 175, 165, 154, 157, 147, 137, 155, 147, 138, 107, 100, 92, 87, 83, 77, 103, 102, 96, 88, 88, 79, 78, 79, 73, 59, 59, 59, 41, 36, 33, 59, 46, 31, 104, 81, 46, 188, 191, 189, 100, 108, 116, 135, 144, 153, 170, 175, 178, 187, 167, 136, 166, 120, 59, 173, 123, 55, 134, 93, 44, 117, 95, 80, 194, 182, 188, 199, 171, 164, 170, 142, 133, 185, 161, 151, 189, 171, 159, 134, 119, 106, 117, 107, 95, 102, 98, 89, 84, 84, 79, 38, 38, 34, 125, 121, 113, 210, 201, 192, 160, 152, 142, 146, 139, 130, 93, 89, 82, 83, 80, 75, 94, 93, 88, 104, 104, 94, 85, 87, 81, 73, 75, 78, 55, 53, 55, 62, 55, 48, 76, 56, 26, 189, 194, 194, 90, 96, 105, 127, 134, 144, 175, 180, 185, 174, 156, 133, 166, 123, 68, 178, 123, 53, 159, 109, 47, 97, 68, 44, 168, 154, 152, 168, 144, 126, 137, 114, 94, 186, 166, 148, 216, 202, 183, 160, 149, 129, 123, 113, 98, 120, 114, 105, 115, 114, 109, 50, 50, 47, 150, 147, 140, 194, 187, 178, 155, 149, 140, 123, 118, 111, 91, 88, 83, 84, 83, 79, 84, 84, 80, 95, 95, 85, 86, 87, 81, 84, 87, 89, 73, 73, 73, 79, 74, 64, 73, 55, 24, 189, 192, 193, 93, 95, 103, 152, 154, 163, 185, 188, 192, 119, 110, 98, 136, 106, 66, 173, 124, 58, 167, 116, 50, 103, 72, 39, 147, 132, 120, 145, 125, 103, 167, 149, 127, 189, 174, 155, 226, 216, 200, 180, 172, 157, 141, 131, 117, 126, 117, 107, 117, 114, 109, 71, 71, 68, 154, 152, 147, 186, 181, 174, 149, 144, 136, 114, 110, 104, 87, 85, 80, 80, 80, 76, 72, 73, 70, 80, 80, 72, 99, 100, 94, 100, 101, 99, 90, 88, 81, 97, 89, 69, 94, 73, 34, 194, 196, 196, 108, 107, 112, 168, 167, 172, 186, 186, 188, 105, 109, 109, 99, 89, 67, 156, 119, 62, 167, 122, 55, 100, 74, 34, 115, 106, 88, 138, 123, 103, 198, 185, 169, 190, 180, 169, 172, 165, 159, 145, 140, 140, 154, 143, 134, 146, 136, 125, 103, 100, 95, 71, 71, 70, 152, 152, 149, 179, 175, 170, 137, 133, 127, 130, 128, 122, 110, 109, 105, 85, 86, 83, 91, 93, 91, 95, 96, 90, 109, 110, 104, 115, 116, 111, 100, 96, 80, 97, 85, 53, 117, 95, 47, 197, 197, 197, 132, 129, 136, 172, 167, 174, 184, 178, 181, 130, 137, 142, 78, 83, 77, 140, 120, 88, 155, 125, 77, 115, 94, 52, 130, 120, 93, 143, 131, 116, 230, 221, 211, 242, 236, 230, 145, 138, 137, 135, 130, 130, 131, 121, 112, 121, 112, 101, 108, 104, 95, 95, 88, 75, 144, 134, 118, 168, 159, 146, 152, 147, 138, 112, 108, 101, 87, 85, 80, 71, 72, 68, 87, 88, 87, 105, 104, 99, 112, 109, 99, 120, 110, 93, 103, 86, 54, 121, 96, 48, 136, 104, 48, 203, 203, 204, 146, 146, 160, 168, 164, 178, 191, 182, 188, 168, 170, 172, 78, 86, 90, 126, 125, 126, 138, 126, 113, 138, 121, 82, 96, 80, 37, 154, 143, 133, 173, 163, 155, 162, 152, 141, 140, 132, 117, 113, 106, 88, 113, 106, 90, 101, 101, 92, 105, 101, 87, 112, 90, 58, 171, 143, 104, 156, 138, 109, 148, 141, 126, 135, 130, 118, 109, 105, 97, 78, 76, 72, 79, 79, 77, 94, 93, 94, 101, 91, 82, 107, 83, 55, 125, 88, 45, 151, 108, 55, 144, 104, 46, 214, 215, 215, 163, 166, 180, 164, 167, 184, 183, 184, 194, 176, 182, 186, 94, 102, 105, 96, 96, 102, 156, 149, 145, 148, 137, 111, 106, 93, 61, 129, 116, 105, 118, 105, 95, 114, 102, 89, 116, 105, 89, 102, 91, 73, 115, 110, 98, 86, 91, 88, 101, 103, 95, 144, 128, 102, 118, 96, 64, 68, 56, 32, 128, 120, 105, 133, 126, 115, 75, 69, 61, 60, 56, 51, 58, 56, 53, 71, 70, 65, 102, 93, 78, 116, 94, 64, 143, 112, 68, 150, 116, 64, 140, 110, 54, 212, 211, 205, 178, 184, 192, 167, 175, 189, 173, 181, 193, 176, 184, 188, 124, 131, 133, 86, 88, 96, 141, 139, 143, 153, 148, 141, 135, 128, 111, 104, 90, 80, 77, 64, 55, 134, 121, 108, 124, 111, 96, 129, 117, 100, 147, 143, 133, 85, 92, 93, 92, 96, 93, 150, 139, 120, 132, 117, 93, 117, 109, 92, 107, 99, 86, 75, 68, 58, 64, 59, 52, 44, 41, 39, 65, 62, 60, 86, 69, 40, 133, 105, 59, 155, 119, 62, 160, 120, 54, 154, 115, 45, 151, 111, 46, 199, 192, 180, 187, 189, 187, 171, 176, 181, 174, 179, 185, 177, 182, 184, 144, 149, 152, 86, 90, 99, 119, 121, 132, 122, 124, 130, 137, 136, 135, 144, 134, 126, 70, 59, 51, 129, 118, 108, 108, 97, 86, 145, 134, 123, 184, 176, 168, 116, 118, 118, 73, 75, 73, 131, 119, 103, 137, 124, 105, 134, 129, 118, 89, 86, 78, 51, 49, 44, 52, 51, 50, 47, 49, 52, 90, 90, 93, 121, 91, 60, 163, 118, 68, 171, 121, 64, 164, 113, 52, 158, 111, 50, 149, 107, 46, 165, 156, 146, 195, 193, 187, 179, 178, 175, 177, 173, 172, 181, 181, 180, 152, 157, 160, 99, 103, 111, 131, 135, 146, 171, 175, 185, 103, 105, 111, 93, 90, 87, 80, 77, 73, 93, 90, 86, 122, 118, 116, 178, 173, 173, 191, 182, 177, 150, 148, 148, 100, 100, 101, 89, 78, 66, 87, 77, 63, 60, 61, 57, 46, 52, 54, 38, 46, 51, 24, 33, 41, 46, 57, 69, 60, 71, 83, 108, 100, 75, 144, 125, 82, 144, 123, 76, 128, 109, 61, 127, 113, 69, 120, 105, 63, 117, 120, 124, 195, 200, 200, 177, 178, 176, 178, 169, 168, 181, 179, 179, 138, 144, 147, 83, 87, 91, 150, 153, 159, 245, 247, 250, 219, 222, 225, 133, 140, 144, 134, 141, 147, 149, 156, 164, 176, 182, 192, 190, 196, 208, 194, 192, 197, 168, 172, 181, 125, 133, 143, 110, 109, 109, 61, 62, 62, 35, 49, 58, 34, 54, 68, 49, 70, 87, 58, 81, 102, 61, 85, 110, 58, 84, 111, 69, 99, 122, 72, 101, 119, 78, 104, 120, 69, 96, 112, 59, 92, 112, 55, 90, 115, 79, 105, 133, 175, 197, 213, 174, 183, 192, 176, 172, 177, 177, 177, 182, 140, 146, 150, 109, 112, 113, 211, 211, 209, 253, 252, 247, 252, 253, 252, 208, 224, 232, 124, 143, 157, 114, 132, 149, 124, 141, 162, 116, 133, 156, 122, 133, 152, 104, 124, 148, 68, 93, 119, 68, 87, 104, 60, 82, 101, 52, 84, 111, 50, 84, 110, 51, 85, 115, 56, 93, 125, 56, 94, 131, 51, 91, 130, 43, 96, 135, 51, 104, 141, 59, 108, 142, 48, 97, 132, 43, 97, 137, 42, 95, 132, 41, 89, 135, 96, 137, 168, 144, 168, 188, 168, 174, 188, 178, 182, 192, 165, 170, 174, 165, 166, 164, 246, 245, 237, 253, 251, 241, 227, 231, 228, 110, 136, 153, 60, 88, 111, 53, 80, 105, 49, 76, 105, 49, 75, 107, 48, 72, 101, 45, 79, 115, 42, 81, 120, 46, 81, 113, 42, 82, 116, 38, 86, 125, 46, 90, 125, 46, 89, 126, 43, 87, 128, 42, 89, 132, 46, 93, 139, 46, 94, 137, 50, 96, 137, 55, 96, 135, 53, 94, 134, 51, 95, 139, 45, 90, 133, 29, 91, 141, 29, 87, 130, 59, 102, 134, 131, 153, 176, 166, 179, 191, 132, 136, 137, 194, 189, 181, 254, 250, 242, 241, 245, 245, 141, 159, 175, 61, 94, 127, 50, 84, 118, 50, 84, 119, 51, 85, 121, 49, 83, 120, 50, 84, 116, 47, 86, 117, 42, 84, 117, 39, 82, 115, 34, 79, 113, 35, 83, 120, 39, 86, 125, 38, 85, 125, 42, 89, 130, 45, 92, 134, 56, 103, 145, 62, 103, 142, 59, 101, 142, 56, 102, 146, 50, 99, 144, 46, 94, 140, 51, 103, 149, 48, 111, 162, 30, 94, 140, 34, 85, 124, 73, 106, 136, 128, 148, 167, 128, 136, 143, 215, 213, 209, 255, 253, 249, 187, 198, 205, 66, 93, 118, 54, 91, 128, 50, 88, 125, 52, 90, 127, 52, 90, 127, 46, 83, 121, 45, 82, 115, 43, 82, 113, 41, 81, 112, 36, 80, 113, 39, 83, 117, 40, 86, 123, 40, 89, 131, 43, 92, 134, 46, 95, 138, 59, 108, 150, 62, 110, 152, 64, 109, 147, 59, 108, 149, 54, 108, 154, 50, 105, 152, 70, 123, 167, 83, 137, 182, 52, 114, 165, 35, 99, 147, 31, 86, 130, 41, 83, 122, 66, 95, 126, 128, 145, 164, 224, 229, 234, 240, 245, 247, 124, 143, 153, 58, 92, 114, 49, 87, 123, 56, 94, 131, 54, 92, 129, 44, 82, 119, 44, 82, 119, 47, 83, 119, 46, 84, 119, 43, 83, 119, 43, 86, 123, 44, 88, 127, 44, 90, 131, 45, 97, 141, 54, 106, 150, 58, 110, 154, 54, 105, 150, 46, 97, 141, 43, 95, 140, 36, 91, 138, 51, 108, 158, 73, 130, 178, 85, 138, 182, 76, 125, 169, 50, 110, 162, 35, 98, 149, 29, 89, 138, 35, 86, 133, 44, 83, 126, 78, 106, 138, 202, 219, 233, 211, 228, 234, 97, 126, 140, 65, 104, 126, 54, 94, 129, 48, 87, 124, 58, 97, 133, 48, 87, 123, 40, 80, 116, 45, 82, 119, 47, 84, 122, 48, 87, 126, 47, 89, 130, 46, 89, 132, 51, 97, 140, 39, 92, 138, 39, 93, 139, 48, 102, 148, 47, 101, 147, 39, 93, 139, 28, 85, 133, 40, 101, 153, 67, 129, 182, 67, 126, 176, 46, 98, 142, 51, 96, 139, 50, 108, 161, 35, 97, 147, 32, 92, 143, 33, 88, 141, 41, 88, 138, 46, 84, 125, 104, 133, 159, 170, 197, 211, 64, 100, 119, 54, 97, 121, 52, 94, 128, 53, 95, 130, 61, 103, 139, 58, 100, 135, 54, 96, 131, 45, 83, 120, 42, 79, 118, 41, 80, 120, 46, 88, 130, 49, 92, 135, 46, 92, 136, 42, 95, 139, 40, 93, 138, 39, 92, 136, 37, 90, 135, 40, 93, 138, 44, 102, 151, 63, 125, 178, 47, 110, 164, 31, 90, 140, 15, 60, 103, 51, 93, 136, 68, 124, 177, 42, 100, 148, 31, 88, 137, 38, 91, 146, 37, 87, 139, 43, 89, 132, 42, 79, 113, 71, 107, 133, 49, 89, 114, 31, 77, 105, 27, 71, 105, 38, 82, 117, 49, 93, 128, 56, 100, 135, 58, 102, 137, 53, 92, 128, 56, 94, 131, 60, 99, 137, 57, 99, 139, 53, 97, 138, 50, 95, 137, 45, 94, 136, 39, 88, 131, 33, 83, 125, 42, 91, 133, 62, 112, 154, 79, 132, 179, 73, 131, 181, 56, 116, 168, 38, 97, 146, 13, 64, 108, 40, 85, 127, 61, 116, 168, 49, 102, 148, 35, 85, 132, 43, 91, 143, 39, 90, 139, 42, 92, 134, 44, 88, 125, 40, 81, 112, 42, 85, 115, 27, 72, 104, 23, 67, 102, 30, 74, 109, 27, 71, 106, 29, 73, 108, 36, 80, 115, 47, 86, 120, 56, 95, 128, 62, 101, 135, 66, 109, 144, 75, 119, 156, 69, 113, 152, 49, 95, 134, 43, 88, 127, 43, 88, 127, 60, 105, 144, 85, 130, 170, 109, 156, 197, 93, 145, 190, 60, 115, 164, 26, 82, 130, 29, 82, 126, 20, 64, 107, 54, 107, 160, 56, 105, 149, 45, 89, 132, 43, 86, 134, 40, 89, 134, 40, 92, 132, 40, 87, 123, 38, 81, 115, 36, 79, 114, 26, 69, 105, 22, 66, 101, 29, 73, 108, 25, 69, 104, 29, 73, 108, 19, 63, 98, 18, 58, 89, 32, 70, 100, 47, 87, 118, 61, 104, 137, 74, 119, 152, 66, 111, 145, 53, 96, 131, 52, 95, 130, 45, 87, 123, 67, 109, 145, 89, 131, 167, 105, 146, 182, 89, 135, 175, 48, 99, 145, 24, 77, 124, 34, 84, 129, 21, 67, 110}

#define IMG_DATA_DOG {91, 64, 30, 82, 58, 30, 87, 73, 59, 89, 87, 83, 95, 92, 80, 98, 90, 71, 97, 87, 68, 94, 90, 75, 92, 93, 84, 98, 94, 85, 81, 76, 66, 28, 26, 19, 15, 15, 10, 18, 19, 16, 19, 19, 20, 19, 19, 20, 16, 16, 17, 15, 15, 16, 13, 15, 13, 10, 16, 8, 10, 14, 10, 13, 13, 12, 15, 14, 8, 26, 24, 12, 29, 25, 15, 26, 21, 12, 39, 34, 25, 25, 20, 11, 18, 13, 6, 22, 13, 13, 22, 15, 13, 18, 13, 10, 94, 65, 34, 79, 56, 30, 90, 78, 59, 124, 120, 106, 144, 138, 118, 133, 121, 96, 111, 97, 71, 101, 94, 71, 98, 96, 81, 94, 88, 79, 48, 41, 35, 14, 9, 6, 12, 10, 7, 11, 11, 9, 14, 13, 14, 16, 14, 16, 24, 23, 24, 32, 30, 32, 26, 26, 26, 27, 28, 24, 22, 22, 20, 22, 19, 15, 52, 48, 32, 67, 61, 36, 56, 45, 24, 57, 45, 24, 67, 55, 34, 60, 49, 26, 42, 29, 10, 36, 19, 7, 61, 46, 32, 47, 36, 26, 94, 66, 39, 86, 65, 40, 120, 105, 82, 156, 142, 119, 155, 138, 111, 147, 125, 93, 135, 112, 79, 123, 105, 76, 114, 103, 81, 88, 78, 65, 41, 32, 22, 39, 32, 25, 42, 38, 32, 40, 37, 31, 49, 48, 32, 51, 50, 33, 58, 57, 41, 56, 55, 38, 47, 45, 31, 30, 28, 21, 38, 33, 28, 29, 21, 14, 53, 44, 27, 55, 45, 21, 41, 26, 7, 71, 54, 29, 53, 36, 12, 63, 47, 20, 63, 45, 21, 54, 33, 14, 82, 64, 42, 59, 46, 32, 89, 69, 42, 108, 90, 67, 136, 112, 88, 133, 101, 72, 130, 95, 63, 126, 88, 52, 124, 85, 48, 126, 92, 60, 124, 100, 74, 85, 72, 51, 47, 38, 19, 54, 48, 30, 61, 56, 41, 94, 90, 75, 84, 81, 59, 84, 81, 57, 61, 58, 35, 69, 66, 43, 74, 71, 48, 45, 39, 24, 48, 39, 28, 32, 20, 11, 37, 23, 11, 54, 40, 20, 56, 39, 20, 73, 56, 35, 58, 41, 21, 44, 27, 9, 66, 46, 24, 80, 56, 34, 72, 54, 33, 32, 22, 8, 72, 60, 33, 94, 78, 56, 105, 75, 51, 106, 62, 33, 134, 86, 53, 123, 73, 36, 109, 59, 20, 117, 70, 36, 113, 77, 47, 88, 70, 41, 61, 51, 23, 64, 57, 32, 75, 69, 47, 99, 94, 74, 72, 66, 51, 82, 76, 63, 69, 63, 50, 49, 43, 30, 48, 42, 27, 75, 68, 45, 64, 54, 36, 47, 33, 23, 62, 46, 31, 68, 52, 31, 54, 37, 21, 47, 31, 17, 56, 39, 26, 40, 24, 10, 32, 15, 4, 46, 25, 14, 36, 20, 8, 25, 19, 5, 43, 37, 16, 54, 39, 20, 62, 35, 16, 83, 45, 24, 127, 81, 51, 123, 73, 39, 105, 53, 17, 110, 57, 21, 102, 53, 16, 97, 65, 25, 79, 59, 27, 66, 56, 33, 87, 81, 62, 75, 69, 53, 86, 80, 66, 80, 74, 60, 67, 60, 46, 71, 65, 52, 77, 72, 55, 88, 82, 58, 66, 58, 41, 50, 40, 30, 62, 53, 37, 62, 52, 30, 58, 42, 24, 31, 15, 3, 40, 26, 10, 38, 26, 11, 31, 20, 8, 23, 10, 6, 29, 15, 8, 27, 16, 6, 47, 42, 26, 46, 29, 11, 47, 19, 3, 67, 30, 11, 111, 66, 36, 116, 69, 35, 101, 51, 15, 105, 52, 14, 105, 51, 12, 107, 61, 21, 89, 58, 27, 56, 40, 20, 56, 49, 33, 67, 63, 46, 77, 71, 55, 68, 62, 46, 74, 68, 51, 75, 69, 53, 78, 72, 54, 76, 70, 48, 49, 42, 26, 52, 44, 32, 52, 45, 29, 51, 43, 20, 72, 56, 34, 59, 43, 24, 63, 50, 30, 56, 44, 27, 37, 28, 13, 28, 20, 6, 45, 33, 13, 34, 22, 5, 69, 60, 46, 71, 50, 31, 68, 35, 17, 66, 25, 2, 98, 54, 22, 109, 64, 30, 102, 54, 17, 110, 60, 21, 112, 59, 19, 111, 55, 19, 97, 53, 26, 62, 40, 21, 48, 42, 25, 52, 50, 32, 60, 55, 39, 82, 76, 60, 75, 69, 53, 57, 51, 35, 46, 40, 23, 81, 75, 54, 60, 52, 36, 41, 33, 22, 55, 48, 31, 41, 33, 14, 39, 23, 6, 61, 45, 24, 55, 42, 24, 49, 38, 21, 40, 31, 15, 29, 21, 5, 49, 36, 11, 45, 32, 8, 79, 60, 44, 112, 87, 67, 134, 100, 78, 104, 65, 39, 114, 73, 40, 118, 75, 40, 109, 64, 27, 111, 64, 24, 108, 57, 17, 103, 48, 12, 95, 52, 25, 66, 44, 26, 56, 50, 34, 59, 57, 40, 82, 77, 60, 75, 69, 53, 75, 69, 53, 68, 62, 46, 73, 67, 51, 73, 67, 46, 64, 57, 40, 42, 34, 23, 52, 45, 29, 44, 36, 16, 50, 34, 15, 53, 37, 16, 42, 29, 11, 45, 34, 17, 52, 41, 26, 42, 29, 18, 44, 27, 13, 38, 21, 8, 120, 87, 66, 129, 98, 77, 158, 128, 107, 136, 105, 83, 127, 90, 58, 116, 76, 39, 109, 66, 28, 114, 69, 28, 106, 59, 17, 100, 54, 14, 114, 81, 50, 93, 77, 57, 65, 58, 43, 63, 58, 42, 72, 66, 51, 71, 65, 50, 99, 93, 77, 95, 89, 73, 107, 101, 83, 100, 94, 71, 64, 57, 41, 46, 38, 27, 40, 34, 18, 45, 37, 15, 51, 34, 14, 54, 38, 17, 43, 29, 11, 40, 29, 14, 49, 39, 24, 53, 39, 20, 53, 33, 16, 36, 17, 5, 161, 120, 94, 126, 93, 70, 135, 108, 90, 143, 117, 100, 144, 108, 79, 126, 86, 52, 102, 62, 26, 110, 68, 30, 105, 61, 21, 118, 86, 46, 170, 149, 118, 156, 146, 124, 115, 110, 92, 114, 107, 90, 123, 117, 100, 126, 120, 104, 152, 146, 130, 144, 137, 122, 114, 107, 90, 113, 107, 85, 115, 108, 91, 120, 112, 100, 109, 102, 85, 85, 77, 57, 81, 65, 46, 67, 52, 31, 51, 38, 18, 54, 40, 22, 54, 40, 19, 60, 44, 16, 82, 63, 31, 76, 57, 29, 164, 126, 100, 130, 103, 78, 99, 72, 51, 129, 94, 76, 159, 114, 93, 152, 111, 90, 123, 91, 69, 112, 80, 54, 118, 83, 53, 151, 131, 107, 189, 178, 159, 173, 167, 148, 149, 145, 122, 154, 146, 122, 178, 165, 147, 177, 169, 152, 175, 170, 152, 170, 162, 146, 140, 128, 114, 141, 134, 117, 172, 165, 149, 179, 171, 156, 178, 171, 155, 172, 164, 148, 159, 149, 135, 127, 118, 99, 100, 87, 62, 97, 72, 44, 89, 59, 31, 59, 35, 12, 63, 41, 18, 87, 69, 44, 161, 125, 95, 147, 116, 88, 125, 89, 65, 144, 100, 80, 146, 105, 87, 141, 111, 95, 161, 138, 124, 156, 133, 115, 169, 145, 122, 186, 170, 153, 182, 171, 153, 162, 151, 131, 147, 138, 113, 161, 150, 124, 173, 155, 136, 174, 162, 144, 178, 173, 154, 178, 170, 154, 172, 160, 146, 174, 166, 150, 183, 176, 160, 173, 166, 150, 169, 162, 146, 184, 176, 162, 178, 169, 158, 172, 164, 147, 145, 133, 108, 115, 89, 60, 99, 67, 38, 83, 60, 37, 66, 49, 28, 53, 40, 21, 163, 124, 89, 159, 119, 88, 163, 118, 92, 166, 120, 98, 97, 73, 52, 81, 66, 52, 155, 142, 132, 180, 167, 155, 195, 181, 164, 188, 174, 157, 154, 136, 115, 131, 110, 85, 137, 118, 92, 164, 146, 121, 147, 125, 102, 150, 135, 112, 183, 176, 155, 186, 178, 162, 185, 174, 162, 186, 178, 163, 189, 183, 166, 182, 175, 159, 169, 163, 146, 182, 174, 160, 182, 172, 162, 178, 170, 156, 179, 169, 148, 145, 123, 100, 122, 94, 70, 139, 121, 96, 125, 113, 90, 44, 38, 21, 168, 126, 92, 172, 128, 99, 172, 128, 102, 146, 110, 84, 59, 51, 23, 51, 48, 28, 138, 130, 120, 177, 169, 160, 192, 186, 172, 169, 158, 139, 126, 104, 78, 124, 93, 62, 139, 110, 81, 153, 127, 103, 133, 106, 79, 139, 120, 93, 184, 175, 152, 193, 185, 169, 193, 183, 172, 195, 187, 172, 198, 191, 175, 198, 191, 175, 190, 183, 167, 188, 179, 166, 191, 180, 171, 194, 186, 174, 199, 191, 175, 179, 161, 144, 146, 122, 103, 167, 147, 125, 181, 169, 146, 99, 97, 74, 177, 129, 103, 178, 133, 110, 168, 133, 110, 118, 99, 71, 57, 63, 26, 43, 46, 18, 114, 106, 92, 173, 165, 154, 192, 189, 174, 163, 153, 133, 131, 103, 73, 149, 108, 70, 149, 109, 78, 142, 110, 87, 133, 100, 71, 156, 133, 103, 195, 184, 159, 197, 190, 173, 198, 189, 179, 200, 192, 177, 203, 196, 180, 205, 198, 182, 195, 188, 172, 192, 182, 169, 201, 188, 181, 204, 196, 186, 203, 197, 185, 189, 175, 163, 140, 117, 106, 137, 111, 95, 170, 154, 130, 129, 127, 96, 182, 135, 115, 177, 136, 116, 153, 129, 104, 96, 94, 61, 70, 85, 41, 58, 66, 30, 98, 91, 72, 164, 155, 142, 192, 187, 172, 180, 171, 151, 169, 144, 115, 172, 131, 95, 154, 111, 80, 140, 103, 77, 137, 101, 67, 176, 152, 121, 201, 191, 168, 197, 189, 173, 200, 190, 177, 200, 192, 177, 203, 197, 180, 204, 197, 181, 191, 185, 168, 191, 183, 169, 202, 190, 184, 204, 197, 188, 204, 199, 189, 189, 180, 171, 145, 127, 117, 115, 86, 69, 129, 106, 81, 113, 103, 68, 182, 142, 123, 165, 133, 110, 121, 109, 77, 83, 93, 51, 73, 93, 45, 62, 77, 35, 76, 79, 51, 152, 143, 129, 193, 181, 172, 201, 195, 179, 198, 187, 165, 181, 157, 131, 160, 128, 101, 147, 110, 79, 140, 103, 63, 176, 154, 125, 195, 188, 173, 194, 184, 171, 196, 180, 163, 193, 185, 169, 197, 191, 175, 193, 187, 171, 191, 185, 169, 197, 190, 176, 202, 195, 186, 201, 195, 186, 198, 192, 182, 183, 177, 166, 145, 133, 117, 117, 90, 65, 131, 97, 71, 123, 95, 66, 182, 144, 125, 138, 114, 88, 89, 89, 51, 75, 95, 48, 71, 94, 44, 61, 77, 34, 44, 50, 20, 113, 108, 90, 183, 171, 161, 205, 197, 186, 206, 198, 183, 193, 179, 160, 183, 165, 142, 163, 140, 112, 141, 111, 77, 167, 148, 125, 183, 176, 168, 183, 172, 164, 185, 169, 156, 189, 181, 165, 190, 184, 168, 185, 179, 163, 194, 188, 172, 199, 194, 179, 200, 195, 182, 196, 188, 175, 183, 170, 156, 166, 147, 133, 144, 120, 101, 137, 103, 77, 150, 108, 83, 138, 100, 74, 161, 128, 108, 103, 91, 60, 75, 86, 44, 69, 95, 46, 68, 91, 43, 69, 85, 42, 46, 54, 22, 53, 54, 31, 138, 133, 116, 197, 187, 178, 205, 195, 186, 194, 186, 172, 187, 181, 162, 178, 170, 148, 164, 144, 120, 168, 154, 138, 169, 162, 156, 167, 158, 153, 182, 168, 160, 188, 181, 166, 178, 172, 156, 182, 176, 160, 197, 190, 174, 199, 195, 178, 197, 194, 177, 184, 174, 156, 154, 130, 112, 149, 113, 94, 162, 120, 99, 162, 119, 95, 163, 116, 93, 148, 105, 81, 128, 108, 83, 83, 83, 48, 71, 89, 45, 68, 93, 45, 68, 89, 42, 70, 87, 43, 68, 80, 43, 44, 51, 20, 77, 78, 53, 173, 165, 152, 197, 188, 178, 195, 189, 176, 177, 174, 159, 164, 161, 144, 164, 154, 134, 158, 149, 134, 153, 146, 136, 153, 145, 137, 161, 152, 143, 162, 156, 141, 152, 146, 130, 171, 166, 149, 197, 191, 175, 199, 194, 178, 200, 195, 180, 172, 159, 142, 128, 101, 82, 150, 110, 88, 177, 130, 107, 177, 130, 107, 174, 127, 105, 159, 114, 91, 97, 92, 62, 75, 87, 48, 71, 90, 45, 73, 91, 45, 73, 90, 46, 73, 90, 46, 74, 89, 48, 68, 80, 42, 46, 53, 23, 135, 130, 110, 191, 182, 166, 197, 189, 173, 170, 161, 146, 132, 124, 109, 109, 106, 87, 107, 103, 84, 113, 106, 90, 100, 93, 80, 95, 89, 77, 96, 89, 75, 81, 74, 60, 127, 121, 106, 188, 182, 166, 196, 190, 176, 204, 194, 188, 175, 159, 150, 116, 89, 73, 135, 98, 77, 178, 134, 110, 182, 137, 114, 183, 141, 117, 175, 136, 111, 79, 87, 50, 70, 88, 46, 69, 89, 44, 74, 91, 46, 76, 92, 48, 75, 91, 48, 76, 91, 50, 74, 89, 48, 46, 57, 20, 105, 102, 79, 190, 182, 164, 198, 188, 171, 168, 155, 141, 119, 108, 93, 66, 70, 45, 55, 60, 32, 63, 65, 36, 61, 63, 35, 53, 57, 30, 60, 63, 37, 56, 57, 32, 65, 62, 41, 152, 145, 127, 193, 184, 172, 202, 191, 185, 199, 185, 175, 148, 128, 112, 121, 97, 76, 161, 131, 105, 183, 146, 119, 177, 141, 113, 173, 136, 110, 72, 90, 43, 69, 88, 41, 69, 90, 42, 71, 91, 44, 74, 89, 46, 72, 85, 43, 77, 89, 48, 77, 89, 48, 54, 64, 26, 91, 88, 68, 189, 181, 167, 194, 186, 172, 164, 155, 141, 140, 133, 118, 85, 93, 62, 62, 74, 37, 63, 74, 34, 75, 87, 43, 75, 88, 43, 71, 87, 43, 74, 84, 42, 52, 53, 19, 86, 76, 56, 152, 139, 131, 177, 170, 163, 164, 157, 149, 135, 127, 118, 103, 95, 86, 111, 99, 84, 155, 132, 105, 156, 126, 99, 162, 124, 99, 70, 92, 42, 72, 90, 42, 73, 87, 40, 74, 84, 39, 80, 86, 48, 87, 91, 56, 97, 100, 65, 104, 108, 73, 86, 88, 56, 103, 96, 78, 190, 181, 167, 187, 178, 164, 161, 152, 137, 162, 154, 139, 106, 102, 80, 79, 76, 50, 79, 76, 48, 89, 88, 55, 89, 87, 53, 82, 78, 44, 82, 77, 42, 73, 65, 36, 56, 42, 28, 66, 53, 55, 71, 69, 84, 47, 46, 64, 41, 40, 57, 44, 43, 61, 45, 42, 53, 80, 69, 61, 125, 105, 91, 159, 127, 107, 70, 91, 45, 74, 87, 44, 84, 88, 48, 95, 95, 57, 106, 101, 71, 115, 108, 81, 117, 110, 83, 125, 118, 90, 114, 106, 81, 121, 111, 93, 197, 185, 169, 185, 174, 157, 160, 149, 132, 152, 140, 124, 115, 99, 85, 104, 86, 72, 98, 81, 66, 99, 81, 66, 96, 77, 61, 96, 72, 54, 93, 72, 52, 85, 70, 53, 80, 68, 63, 49, 43, 52, 24, 32, 55, 23, 33, 57, 26, 36, 60, 26, 36, 61, 26, 34, 57, 31, 32, 48, 59, 50, 56, 111, 92, 82, 75, 88, 53, 84, 90, 58, 101, 100, 70, 111, 105, 78, 109, 98, 76, 109, 97, 77, 111, 98, 79, 114, 102, 82, 106, 93, 74, 118, 106, 87, 190, 177, 159, 187, 174, 156, 151, 139, 121, 126, 113, 95, 110, 92, 78, 111, 90, 78, 99, 78, 68, 98, 77, 69, 103, 80, 74, 104, 76, 70, 102, 80, 71, 90, 79, 71, 62, 58, 60, 33, 38, 49, 21, 38, 51, 21, 39, 52, 21, 39, 52, 20, 38, 50, 22, 38, 55, 25, 34, 60, 28, 30, 47, 43, 37, 41, 91, 91, 73, 104, 104, 86, 108, 105, 88, 104, 99, 83, 100, 92, 75, 100, 90, 73, 100, 90, 73, 103, 93, 76, 95, 85, 67, 101, 87, 68, 179, 164, 144, 189, 174, 154, 133, 118, 98, 91, 77, 56, 99, 87, 66, 115, 102, 85, 110, 97, 83, 113, 99, 90, 123, 108, 103, 116, 102, 99, 108, 101, 94, 76, 78, 73, 34, 42, 49, 23, 36, 51, 21, 39, 51, 20, 39, 50, 20, 38, 50, 22, 40, 52, 20, 37, 52, 22, 32, 56, 24, 31, 53, 24, 30, 46, 105, 98, 88, 103, 98, 88, 102, 99, 88, 96, 93, 82, 95, 88, 75, 94, 86, 74, 95, 87, 77, 97, 88, 77, 96, 84, 71, 117, 102, 81, 176, 162, 139, 175, 163, 141, 106, 94, 74, 68, 59, 38, 102, 95, 72, 116, 109, 88, 114, 106, 88, 125, 117, 101, 135, 126, 113, 126, 120, 111, 97, 98, 95, 39, 48, 53, 19, 33, 45, 19, 35, 52, 18, 33, 54, 18, 34, 55, 20, 35, 56, 23, 39, 59, 23, 37, 59, 22, 34, 54, 17, 33, 49, 22, 33, 55, 106, 97, 88, 103, 96, 86, 103, 99, 88, 104, 100, 88, 109, 98, 88, 108, 98, 92, 102, 94, 92, 105, 93, 89, 119, 102, 92, 151, 133, 111, 179, 164, 140, 147, 136, 115, 105, 97, 79, 109, 103, 86, 125, 112, 96, 129, 115, 99, 130, 117, 100, 129, 117, 99, 124, 113, 93, 122, 112, 96, 75, 75, 77, 20, 29, 49, 17, 32, 51, 19, 34, 49, 18, 32, 54, 19, 34, 57, 20, 35, 58, 18, 34, 57, 21, 33, 58, 20, 34, 52, 14, 37, 43, 21, 32, 55, 114, 103, 91, 114, 104, 92, 120, 110, 98, 125, 114, 102, 132, 117, 102, 125, 113, 102, 112, 105, 97, 115, 104, 94, 139, 121, 106, 164, 140, 120, 163, 139, 119, 129, 108, 90, 129, 110, 95, 144, 125, 112, 142, 117, 106, 139, 114, 102, 134, 113, 99, 125, 107, 93, 125, 109, 94, 112, 103, 92, 50, 52, 57, 20, 30, 51, 20, 35, 56, 22, 36, 53, 21, 36, 58, 22, 37, 60, 24, 38, 61, 21, 36, 59, 21, 34, 57, 36, 47, 61, 37, 50, 55, 22, 30, 51, 136, 121, 106, 131, 115, 100, 133, 114, 100, 134, 113, 99, 130, 108, 91, 129, 113, 97, 126, 117, 104, 118, 109, 92, 126, 109, 89, 145, 115, 100, 142, 108, 94, 141, 108, 95, 150, 117, 104, 147, 113, 101, 143, 108, 98, 144, 111, 102, 140, 112, 104, 141, 118, 110, 137, 119, 112, 74, 69, 67, 30, 36, 45, 23, 37, 56, 23, 37, 60, 26, 38, 60, 24, 39, 61, 25, 40, 63, 25, 40, 62, 23, 38, 61, 24, 39, 59, 80, 84, 92, 78, 72, 76, 28, 31, 50}

static uint8_t img_data[] = IMG_DATA_CAT;

void imgdata_preprocess(int8_t *img_buffer)
{
    int32_t i = 0;
    int32_t mean_data[3]   = INPUT_MEAN_SHIFT;
    uint32_t scale_data[3] = INPUT_RIGHT_SHIFT;

    printf("image data is [cat]\r\n");

    for (i=0; i < 32*32*3; i += 3) {
        img_buffer[i] =   (int8_t)__SSAT( ((((int)img_data[i]   - mean_data[0])<<7) + (0x1<<(scale_data[0]-1)))
                                >> scale_data[0], 8);
        img_buffer[i+1] = (int8_t)__SSAT( ((((int)img_data[i+1] - mean_data[1])<<7) + (0x1<<(scale_data[1]-1)))
                                >> scale_data[1], 8);
        img_buffer[i+2] = (int8_t)__SSAT( ((((int)img_data[i+2] - mean_data[2])<<7) + (0x1<<(scale_data[2]-1)))
                                >> scale_data[2], 8);
    }
}
