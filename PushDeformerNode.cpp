#include "PushDeformerNode.h"
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnMesh.h>
#include <maya/MFloatVectorArray.h>
#include <maya/MItGeometry.h>



// CONSTANTS

static const MTypeId TYPE_ID = MTypeId(0x0004f4fe);
static const MString TYPE_NAME = "pushdeformernode";

// STATIC VARIABLES

MObject PushDeformerNode::pushObj;

// PUBLIC METHODS

PushDeformerNode::PushDeformerNode() :MPxDeformerNode(){};
PushDeformerNode::~PushDeformerNode() {};


MStatus PushDeformerNode::deform(MDataBlock& dataBlock, MItGeometry& geoIter, const MMatrix& matrix, unsigned int multiIndex)
{
	float envelopeValue = dataBlock.inputValue(envelope).asFloat();
	if (envelopeValue == 0)
	{
		return MS::kSuccess;
	}
	float pushValue = dataBlock.inputValue(pushObj).asFloat();

	MArrayDataHandle inputHandle = dataBlock.outputArrayValue(input);
	inputHandle.jumpToElement(multiIndex);
	MDataHandle inputElementHandle = inputHandle.outputValue();

	MObject inputGeomObj = inputElementHandle.child(inputGeom).asMesh();
	MFnMesh meshFn(inputGeomObj);

	MFloatVectorArray normals;
	meshFn.getVertexNormals(false, normals);

	MPoint ptLocal;
	MFloatVector normal;
	MFloatVector targetVector;

	geoIter.reset();
	while (!geoIter.isDone())
	{
		float sourceWeight = weightValue(dataBlock, multiIndex, geoIter.index());
		ptLocal = geoIter.position();
		normal = normals[geoIter.index()];

		targetVector = ptLocal + (normal*pushValue)*sourceWeight*envelopeValue;
		geoIter.setPosition(targetVector);

		geoIter.next();
	}
	return MS::kSuccess;
}


void* PushDeformerNode::creator()
{
	return new PushDeformerNode();
}

MStatus PushDeformerNode::initialize()
{
	MFnNumericAttribute numericAttr;
	pushObj = numericAttr.create("pushVertex", "push", MFnNumericData::kFloat, 0.0f);
	numericAttr.setKeyable(true);

	addAttribute(pushObj);
	attributeAffects(pushObj, outputGeom);

	return MS::kSuccess;
}


MTypeId PushDeformerNode::GetTypeId()
{
	return TYPE_ID;
}

MString PushDeformerNode::GetTypeName()
{
	return TYPE_NAME;
}