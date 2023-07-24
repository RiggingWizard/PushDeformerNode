#include "PushDeformerNode.h"
#include <maya/MFnPlugin.h>
#include <maya/MGlobal.h>

MStatus initializePlugin(MObject pluginObj)
{
	const char* vendor = "Dikshant Kumar";
	const char* version = "1.0.0";
	const char* requiredApiVersion = "Any";

	MStatus status;
	MFnPlugin pluginFn(pluginObj, vendor, version, requiredApiVersion, &status);

	if (!status)
	{
		MGlobal::displayError("Failed to initialize plugin: " + status.errorString());
		return status;
	}
	status = pluginFn.registerNode(PushDeformerNode::GetTypeName(),
								   PushDeformerNode::GetTypeId(),
								   PushDeformerNode::creator,
								   PushDeformerNode::initialize,
								   MPxNode::kDeformerNode);
	if (!status)
	{
		MGlobal::displayError("Failed to register node: " + PushDeformerNode::GetTypeName());
		return status;
	}

	return MS::kSuccess;
}

MStatus uninitializePlugin(MObject pluginObj)
{
	MStatus status;

	MFnPlugin pluginFn(pluginObj);
	status = pluginFn.deregisterNode(PushDeformerNode::GetTypeId());
	if (!status)
	{
		MGlobal::displayError("Failed to deregister node: " + PushDeformerNode::GetTypeName());
		return status;
	}
	return MS::kSuccess;
}