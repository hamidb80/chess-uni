#pragma once
using namespace System;

generic<class Type>
	ref class UiEventLambdaWrapper {
	public:
		Type valToPass;
		Action<Type>^ nextFunc;
		void func(Object^ sender, EventArgs^ e) {
			nextFunc(valToPass);
		}
	};