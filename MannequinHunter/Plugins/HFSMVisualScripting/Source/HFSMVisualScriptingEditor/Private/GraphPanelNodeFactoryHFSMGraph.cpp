// Fill out your copyright notice in the Description page of Project Settings.


#include "GraphPanelNodeFactoryHFSMGraph.h"
#include "EdGraph/EdGraphNode.h"

TSharedPtr<class SGraphNode> FGraphPanelNodeFactoryHFSMGraph::CreateNode(UEdGraphNode* node) const
{
	//if (UEdNode_GenericGraphNode* EdNode_GraphNode = Cast<UEdNode_GenericGraphNode>(node))
	//{
	//	return SNew(SEdNode_GenericGraphNode, EdNode_GraphNode);
	//}
	//else if (UEdNode_GenericGraphEdge* EdNode_Edge = Cast<UEdNode_GenericGraphEdge>(node))
	//{
	//	return SNew(SEdNode_GenericGraphEdge, EdNode_Edge);
	//}
	return nullptr;
}
