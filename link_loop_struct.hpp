#ifndef link_loop_struct_hpp
#define link_loop_struct_hpp
#include<iostream>
#include<memory>
#include<string>
#include<exception>
using std::string;
using std::shared_ptr;
using std::initializer_list;
using std::shared_ptr;
using std::make_shared;
using std::out_of_range;
namespace xc_std {
	template<class T>
	struct template_info {
		shared_ptr<template_info<T>> n_struct;
		shared_ptr<T> info;
		bool is_used;
	};
	template<class T>
	shared_ptr<template_info<T>> get_struct() {
		auto ret = make_shared<template_info<T>>();
		ret->info = nullptr;
		ret->is_used = false;
		return ret;
	}
	template<class T>
	class link_loop_struct
	{
	public:
		link_loop_struct() {
			auto loop_head = get_struct<T>();
			info_base = loop_head;
			loop_head->n_struct = loop_head;
			size = 0;
		}
		~link_loop_struct() {
			auto delete_ptr = info_base;
			do {
				auto next_ptr = delete_ptr->n_struct;
				delete_ptr->n_struct = nullptr;
				delete_ptr = next_ptr;
			} while (delete_ptr != nullptr);
		}
		void push_back(const T info) {
			auto head_ptr = info_base;
			if (!head_ptr->is_used) {//check if head is empty
				head_ptr->info = make_shared<T>(info);
				head_ptr->is_used = true;
				size++;
			}
			else {
				auto insert_ptr = get_unused_ptr();
				insert_ptr->info = make_shared<T>(info);
				insert_ptr->is_used = true;
				size++;
			}

		}
		T pop_front() {
			T ret;
			auto head_ptr = info_base;
			auto next_ptr = head_ptr->n_struct;
			auto tail_ptr = get_tail();
			if (size - 1 >= 0) {
				ret = *(head_ptr->info);
				tail_ptr->n_struct = next_ptr;
				head_ptr->is_used = false;
			//	head_ptr->info.reset();
				head_ptr->info = nullptr;
				head_ptr.reset();
				info_base = next_ptr;
				size--;
			}
			else {
				reset_info();
				memset(&ret,0,sizeof(T));
			}
			return ret;
		}
	private:
		int size;
		shared_ptr<template_info<T>> info_base;
		void reset_info() {
			auto loop_head = get_struct<T>();
			info_base->n_struct = nullptr;//release struct resource
			info_base->info = nullptr;//release storage information
			info_base.reset();//release pointer
			info_base = loop_head;//->new pointer
			loop_head->n_struct = loop_head;
			size = 0;
		}

		shared_ptr<template_info<T>> get_unused_ptr() {
			auto tail_ptr = get_tail();
			auto new_ptr = get_struct<T>();
			new_ptr->n_struct = tail_ptr->n_struct;
			tail_ptr->n_struct = new_ptr;
			return new_ptr;
		}
		shared_ptr<template_info<T>> get_tail() {
			auto get_tail_ptr = info_base;
			do {
				get_tail_ptr = get_tail_ptr->n_struct;
			} while (get_tail_ptr->n_struct != info_base);
			return get_tail_ptr;
		}
		shared_ptr<template_info<T>> get_used_ptr(shared_ptr<template_info<T>> ptr) {
			auto head = info_base;
			auto move_ptr = head->n_struct;
			while (move_ptr != head) {
				if (move_ptr.get() == ptr.get()) {
					return move_ptr;
				}
				move_ptr = move_ptr->n_struct;
			}
			return make_shared<template_info<T>>(nullptr);
		}
	};
}
#endif

