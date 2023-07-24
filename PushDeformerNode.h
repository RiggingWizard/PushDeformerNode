#pragma once

#include <maya/MPxDeformerNode.h>

class PushDeformerNode : public MPxDeformerNode
{
public:
	PushDeformerNode();
	virtual ~PushDeformerNode() override;

	virtual MStatus deform(MDataBlock& dataBlock, MItGeometry& geoIter, const MMatrix& matrix, unsigned int multiIndex) override;

	// Static Methods

	static void* creator();
	static MStatus initialize();
	static MTypeId GetTypeId();
	static MString GetTypeName();

private:
	static MObject pushObj;
};