// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <stack>

/**
 * 
 */

using namespace std;

namespace CommandListKeyTypeCheck
{
	template<typename TKey>
 	inline void Check()
	{
		static_assert(!std::is_class<TKey>::value, "TCommandListTree key cannot use a class ");
	}
}

template<typename TKey, typename TValue>
class TCommandListNode : public TSharedFromThis<TCommandListNode<TKey, TValue>>
{
public:
	TCommandListNode()
	{
		CommandListKeyTypeCheck::Check<TKey>();
	}
	TCommandListNode(TKey key, const TSharedPtr<TValue>& value)
	{
		CommandListKeyTypeCheck::Check<TKey>();
		this->key = key;
		this->value = value;
	}

	TCommandListNode(TKey key, TValue* value)
	{
		CommandListKeyTypeCheck::Check<TKey>();
		this->key = key;
		this->value = MakeShared<TValue>(value);
	}
	~TCommandListNode()
	{
		childs.Reset();
	}

	TSharedPtr<TCommandListNode<TKey, TValue>>* AddChild(TKey _key, const TValue* _value)
	{
		TSharedPtr<TCommandListNode<TKey, TValue>>* find = childs.FindByPredicate([this, &_key](const TSharedPtr<TCommandListNode<TKey, TValue>>& data)
			{
				return data->GetKey() == _key;
			});

		if (find == nullptr)
		{
			TSharedPtr<TValue> tValue = nullptr;
			if (_value)
			{
				tValue = MakeShared<TValue>();
				TValue* pValue = ((tValue).Get());
				*pValue = *_value;
			}
			TSharedPtr<TCommandListNode<TKey, TValue>> addNode = MakeShared<TCommandListNode<TKey, TValue>>(_key, tValue);
			int32 index = childs.Add(addNode);


			return &childs[index];
		}
		return find;
	}

	inline const TSharedPtr<TCommandListNode<TKey, TValue>>* FindChild(TKey findKey) 
	{
		return childs.FindByPredicate([findKey](const TSharedPtr<TCommandListNode<TKey, TValue>>& data)
			{
				return data->GetKey() == findKey;
			});
	}

	inline TKey GetKey() const { return key; }
	inline const TSharedPtr<TValue>* GetValue() const { return &value; };
	inline const TSharedPtr<TCommandListNode<TKey, TValue>>& GetChild(int index) { return childs[index]; }
	inline const TArray<TSharedPtr<TCommandListNode<TKey, TValue>>>& GetChilds() const { return childs; }
private:
	TKey key;
	TSharedPtr<TValue> value = nullptr;
	TArray<TSharedPtr<TCommandListNode<TKey, TValue>>> childs = {};
};


template<typename TKey, typename TValue>
class TCommandListTree
{

public:
	TCommandListTree()
	{
		
		CommandListKeyTypeCheck::Check<TKey>();
	
		root = MakeShared<TCommandListNode<TKey, TValue>>();
	}
	~TCommandListTree()
	{
		root = nullptr;
	}

	TSharedPtr<TCommandListNode<TKey, TValue>>* AddTree(TKey key, const TValue* value, const TSharedPtr<TCommandListNode<TKey, TValue>>* parent = nullptr)
	{
		if (parent == nullptr)
		{
			return root->AddChild(key, value);
		}

		return (*parent)->AddChild(key, value);
	}

	TSharedPtr<TCommandListNode<TKey, TValue>> GetRoot() const { return root; }

	void ForEach(std::function<void(TSharedPtr<TCommandListNode<TKey, TValue>>&)> process = nullptr)
	{
		stack<TSharedPtr<TCommandListNode<TKey, TValue>>> nodeStack;

		nodeStack.push(root);

		while (!nodeStack.empty())
		{
			TSharedPtr<TCommandListNode<TKey, TValue>> node = nodeStack.top();
			nodeStack.pop();

			if (process != nullptr)
				process(node);

			const TArray<TSharedPtr<TCommandListNode<TKey, TValue>>>& childs = node->GetChilds();

			for(const TSharedPtr<TCommandListNode<TKey, TValue>> child : childs)
			{
				nodeStack.push(child);
			}
		}
	}

	const TSharedPtr<TCommandListNode<TKey, TValue>> Find(TKey key)
	{
		stack<TSharedPtr<TCommandListNode<TKey, TValue>>> nodeStack;

		nodeStack.push(root);

		while (!nodeStack.empty())
		{
			TSharedPtr<TCommandListNode<TKey, TValue>> node = nodeStack.top();
			nodeStack.pop();

			if (node->GetKey() == key)
				return node;


			const TArray<TSharedPtr<TCommandListNode<TKey, TValue>>>& childs = node->GetChilds();

			for (const TSharedPtr<TCommandListNode<TKey, TValue>> child : childs)
			{
				nodeStack.push(child);
			}
		}

		return nullptr;
	}

private:
	TSharedPtr<TCommandListNode<TKey, TValue>> root;

};