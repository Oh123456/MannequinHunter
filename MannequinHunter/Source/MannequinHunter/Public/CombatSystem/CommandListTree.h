// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

template<typename TEnum, typename TValue>
class TCommandListNode : public TSharedFromThis<TCommandListNode<TEnum, TValue>>
{
public:
	TCommandListNode()
	{
		static_assert(std::is_enum<TEnum>::value, "TCommandListNode Value is Only Enum");
	}
	TCommandListNode(TEnum key, const TSharedPtr<TValue>& value)
	{
		static_assert(std::is_enum<TEnum>::value, "TCommandListNode Value is Only Enum");

		this->key = key;
		this->value = value;
	}
	~TCommandListNode()
	{
		childs.Reset();
	}

	TSharedPtr<TCommandListNode<TEnum, TValue>>* AddChild(TEnum _key, const TSharedPtr<TValue>& _value)
	{
		TSharedPtr<TCommandListNode<TEnum, TValue>>* find = childs.FindByPredicate([this, &_key](const TSharedPtr<TCommandListNode<TEnum, TValue>>& data)
			{
				return data->GetKey() == _key;
			});

		if (find == nullptr)
		{
			TSharedPtr<TCommandListNode<TEnum, TValue>> addNode = MakeShared<TCommandListNode<TEnum, TValue>>(_key, _value);
			int32 index = childs.Add(addNode);


			return &childs[index];
		}
		return find;
	}

	inline TEnum GetKey() const { return key; }
	inline const TValue* GetValue() const { return value; };
	inline const TSharedPtr<TCommandListNode<TEnum, TValue>>& GetChild(int index) { return childs[index]; }
	inline const TArray<TSharedPtr<TCommandListNode<TEnum, TValue>>>& GetChilds() const { return childs; }
private:
	TEnum key;
	TSharedPtr<TValue> value = nullptr;
	TArray<TSharedPtr<TCommandListNode<TEnum, TValue>>> childs = {};
};


template<typename TEnum, typename TValue>
class TCommandListTree
{

public:
	TCommandListTree()
	{
		static_assert(std::is_enum<TEnum>::value, "TCommandListTree Value is Only Enum");
	
		root = MakeShared<TCommandListNode<TEnum, TValue>>();
	}
	~TCommandListTree()
	{
		root = nullptr;
	}

	TSharedPtr<TCommandListNode<TEnum, TValue>>* AddTree(TEnum key, const TSharedPtr<TValue>& value, const TSharedPtr<TCommandListNode<TEnum, TValue>>* parent = nullptr)
	{
		if (parent == nullptr)
		{
			return root->AddChild(key, value);
		}

		return (*parent)->AddChild(key, value);
	}

private:
	TSharedPtr<TCommandListNode<TEnum, TValue>> root;

};