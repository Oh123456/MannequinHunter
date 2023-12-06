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

	TCommandListNode(TEnum key, TValue* value)
	{
		static_assert(std::is_enum<TEnum>::value, "TCommandListNode Value is Only Enum");

		this->key = key;
		this->value = MakeShared<TValue>(value);
	}
	~TCommandListNode()
	{
		childs.Reset();
	}

	TSharedPtr<TCommandListNode<TEnum, TValue>>* AddChild(TEnum _key, const TValue* _value)
	{
		TSharedPtr<TCommandListNode<TEnum, TValue>>* find = childs.FindByPredicate([this, &_key](const TSharedPtr<TCommandListNode<TEnum, TValue>>& data)
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
			TSharedPtr<TCommandListNode<TEnum, TValue>> addNode = MakeShared<TCommandListNode<TEnum, TValue>>(_key, tValue);
			int32 index = childs.Add(addNode);


			return &childs[index];
		}
		return find;
	}

	inline const TSharedPtr<TCommandListNode<TEnum, TValue>>* FindChild(TEnum findKey) 
	{
		return childs.FindByPredicate([findKey](const TSharedPtr<TCommandListNode<TEnum, TValue>>& data)
			{
				return data->GetKey() == findKey;
			});
	}

	inline TEnum GetKey() const { return key; }
	inline const TSharedPtr<TValue>* GetValue() const { return &value; };
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

	TSharedPtr<TCommandListNode<TEnum, TValue>>* AddTree(TEnum key, const TValue* value, const TSharedPtr<TCommandListNode<TEnum, TValue>>* parent = nullptr)
	{
		if (parent == nullptr)
		{
			return root->AddChild(key, value);
		}

		return (*parent)->AddChild(key, value);
	}

	TSharedPtr<TCommandListNode<TEnum, TValue>> GetRoot() const { return root; }

private:
	TSharedPtr<TCommandListNode<TEnum, TValue>> root;

};