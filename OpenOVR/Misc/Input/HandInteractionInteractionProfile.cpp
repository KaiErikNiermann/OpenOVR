//
// XR_EXT_hand_interaction, see the header.
//

#include "stdafx.h"

#include "HandInteractionInteractionProfile.h"

HandInteractionInteractionProfile::HandInteractionInteractionProfile()
{
	const char* sides[] = {
		"/user/hand/left",
		"/user/hand/right",
		nullptr
	};
	const char* inputs[] = {
		"/input/aim/pose",
		"/input/grip/pose",
		"/input/pinch_ext/pose",
		"/input/poke_ext/pose",
		"/input/pinch_ext/value",
		"/input/pinch_ext/ready_ext",
		"/input/aim_activate_ext/value",
		"/input/aim_activate_ext/ready_ext",
		"/input/grasp_ext/value",
		"/input/grasp_ext/ready_ext",
		nullptr
	};

	for (const char** side = sides; *side; side++) {
		for (const char** input = inputs; *input; input++) {
			validInputPaths.insert(std::string(*side) + std::string(*input));
		}
	}

	// A pinch is the hand's trigger, a grasp its grip
	pathTranslationMap = {
		{ "trigger/value", "pinch_ext/value" },
		{ "trigger/click", "pinch_ext/value" },
		{ "trigger/touch", "pinch_ext/ready_ext" },
		{ "grip/value", "grasp_ext/value" },
		{ "grip/click", "grasp_ext/value" },
		{ "grip/touch", "grasp_ext/ready_ext" },
	};
}

const std::string& HandInteractionInteractionProfile::GetPath() const
{
	static std::string interactionPath = "/interaction_profiles/ext/hand_interaction_ext";
	return interactionPath;
}

std::optional<const char*> HandInteractionInteractionProfile::GetLeftHandRenderModelName() const
{
	return std::nullopt;
}

std::optional<const char*> HandInteractionInteractionProfile::GetRightHandRenderModelName() const
{
	return std::nullopt;
}

std::optional<const char*> HandInteractionInteractionProfile::GetOpenVRName() const
{
	return std::nullopt;
}

std::optional<vr::EVRSkeletalTrackingLevel> HandInteractionInteractionProfile::GetOpenVRTrackinglevel() const
{
	// The skeleton comes from tracked joints, not estimated from buttons
	return vr::VRSkeletalTracking_Full;
}

const InteractionProfile::LegacyBindings* HandInteractionInteractionProfile::GetLegacyBindings(const std::string& handPath) const
{
	static LegacyBindings bindings = {};
	if (!bindings.trigger) {
		// No sticks, buttons or haptics: a hand has a pinch, a grasp and its poses
		bindings.trigger = "input/pinch_ext/value";
		bindings.triggerClick = "input/pinch_ext/value";
		bindings.triggerTouch = "input/pinch_ext/ready_ext";
		bindings.grip = "input/grasp_ext/value";

		bindings.gripPoseAction = "input/grip/pose";
		bindings.aimPoseAction = "input/aim/pose";
	}
	return &bindings;
}
