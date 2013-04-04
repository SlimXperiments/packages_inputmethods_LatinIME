/*
 * Copyright (C) 2013 The Android Open Source Project
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

#ifndef LATINIME_WEIGHTING_H
#define LATINIME_WEIGHTING_H

#include "defines.h"

namespace latinime {

class DicNode;
class DicTraverseSession;
struct DicNode_InputStateG;

class Weighting {
 public:
    static void addCostAndForwardInputIndex(const Weighting *const weighting,
            const CorrectionType correctionType,
            const DicTraverseSession *const traverseSession,
            const DicNode *const parentDicNode, DicNode *const dicNode,
            hash_map_compat<int, int16_t> *const bigramCacheMap);

 protected:
    virtual float getTerminalSpatialCost(const DicTraverseSession *const traverseSession,
            const DicNode *const dicNode) const = 0;

    virtual float getOmissionCost(
         const DicNode *const parentDicNode, const DicNode *const dicNode) const = 0;

    virtual float getMatchedCost(
            const DicTraverseSession *const traverseSession, const DicNode *const dicNode,
            DicNode_InputStateG *inputStateG) const = 0;

    virtual bool isProximityDicNode(const DicTraverseSession *const traverseSession,
            const DicNode *const dicNode) const = 0;

    virtual float getTranspositionCost(
            const DicTraverseSession *const traverseSession, const DicNode *const parentDicNode,
            const DicNode *const dicNode) const = 0;

    virtual float getInsertionCost(
            const DicTraverseSession *const traverseSession,
            const DicNode *const parentDicNode, const DicNode *const dicNode) const = 0;

    virtual float getNewWordCost(const DicNode *const dicNode) const = 0;

    virtual float getNewWordBigramCost(
            const DicTraverseSession *const traverseSession, const DicNode *const dicNode,
            hash_map_compat<int, int16_t> *const bigramCacheMap) const = 0;

    virtual float getCompletionCost(
            const DicTraverseSession *const traverseSession,
            const DicNode *const dicNode) const = 0;

    virtual float getTerminalLanguageCost(
            const DicTraverseSession *const traverseSession, const DicNode *const dicNode,
            float dicNodeLanguageImprobability) const = 0;

    virtual bool needsToNormalizeCompoundDistance() const = 0;

    virtual float getAdditionalProximityCost() const = 0;

    virtual float getSubstitutionCost() const = 0;

    virtual float getSpaceSubstitutionCost() const = 0;

    Weighting() {}
    virtual ~Weighting() {}

 private:
    DISALLOW_COPY_AND_ASSIGN(Weighting);

    static float getSpatialCost(const Weighting *const weighting,
            const CorrectionType correctionType, const DicTraverseSession *const traverseSession,
            const DicNode *const parentDicNode, const DicNode *const dicNode,
            DicNode_InputStateG *const inputStateG);
    static float getLanguageCost(const Weighting *const weighting,
            const CorrectionType correctionType, const DicTraverseSession *const traverseSession,
            const DicNode *const parentDicNode, const DicNode *const dicNode,
            hash_map_compat<int, int16_t> *const bigramCacheMap);
    // TODO: Move to TypingWeighting and GestureWeighting?
    static bool isEditCorrection(const CorrectionType correctionType);
    // TODO: Move to TypingWeighting and GestureWeighting?
    static bool isProximityCorrection(const Weighting *const weighting,
            const CorrectionType correctionType, const DicTraverseSession *const traverseSession,
            const DicNode *const dicNode);
    // TODO: Move to TypingWeighting and GestureWeighting?
    static int getForwardInputCount(const CorrectionType correctionType);
};
} // namespace latinime
#endif // LATINIME_WEIGHTING_H
