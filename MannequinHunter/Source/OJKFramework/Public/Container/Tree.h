// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <stack>

template<typename TKey, typename TValue>
class TTreeNode
{
public:

	TTreeNode()
	{

	}

	TTreeNode(const TKey& keyValue, const TValue* tValue = nullptr)
	{
		key = keyValue;
		CreateValue(tValue);
	}

	~TTreeNode()
	{
		value = nullptr;
		// 일단 노드 삭제는 고려 안함
		childes.Empty();
	}

	void AddChilde(const TKey& keyValue, const TValue* tValue)
	{
		TSharedPtr<TTreeNode>* findNode = childes.FindByPredicate([&keyValue](const TSharedPtr<TTreeNode>& nodeData)
			{
				return (nodeData->GetKey() == keyValue);
			});

		if (findNode == nullptr)
		{
			TSharedPtr<TTreeNode> newChild = MakeShared<TTreeNode>(keyValue, tValue);
			childes.Add(newChild);
		}
	}

	inline const TArray<TSharedPtr<TTreeNode>>& GetChildes() const { return childes; }
	inline const TKey& GetKey() const { return key; }
	inline const TSharedPtr<TValue>* GetValue() const { return &value; }
private:
	void CreateValue(const TValue* tValue)
	{
		if (tValue == nullptr)
			return;

		childes = MakeShared<TValue>();
		(*childes) = *tValue;
	}
private:
	TKey key;
	TSharedPtr<TValue> value;
	TArray<TSharedPtr<TTreeNode>> childes;
};


template<typename TKey, typename TValue>
class OJKFRAMEWORK_API TTree
{
	using TreeNode = TTreeNode<TKey, TValue>;
public:
	TTree()
	{
		root = MakeShared<TreeNode>();
	}


	void Add(const TKey& parentsKey, const TKey& key, const TValue* value)
	{
		TSharedPtr<TreeNode> findNode = Find(parentsKey);
		if (findNode == nullptr)
			root->AddChilde(key, value);
		else
			findNode->AddChilde(key, value);
	}

	void AddRootChilde(const TKey& key, const TValue* value)
	{
		root->AddChilde(key, value);
	}

	TSharedPtr<TreeNode> Find(const TKey& key)
	{
		std::stack<TSharedPtr<TreeNode>> stack;

		stack.push(root);

		while (!stack.empty())
		{
			TSharedPtr<TreeNode>& node = stack.top();
			stack.pop();
			if (node == nullptr)
				continue;
			if (node->GetKey() == key)
				return node;
			const TArray<TSharedPtr<TTreeNode>> childs = node->GetGetChildes();
			for (TSharedPtr<TTreeNode>& child : childs)
			{
				stack.push(child);
			}

		}

		return nullptr;
	}

	void ForEach(std::function<void(TSharedPtr<TreeNode>&)> process = nullptr)
	{
		std::stack<TSharedPtr<TreeNode>> stack;

		stack.push(root);

		while (!stack.empty())
		{
			TSharedPtr<TreeNode>& node = stack.top();
			stack.pop();
			if (node == nullptr)
				continue;

			process(node);

			const TArray<TSharedPtr<TreeNode>> childs = node->GetGetChildes();
			for (TSharedPtr<TreeNode>& child : childs)
			{
				stack.push(child);
			}

		}
	}

	const TSharedPtr<TreeNode>& GetRoot() const { return root; }

private:
	TSharedPtr<TreeNode> root;
};
