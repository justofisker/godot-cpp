/*************************************************************************/
/*  variant.cpp                                                          */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2022 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2022 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include <godot_cpp/variant/variant.hpp>

#include <godot_cpp/godot.hpp>

#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/core/defs.hpp>

#include <utility>

namespace godot {

GDNativeVariantFromTypeConstructorFunc Variant::from_type_constructor[Variant::VARIANT_MAX]{};
GDNativeTypeFromVariantConstructorFunc Variant::to_type_constructor[Variant::VARIANT_MAX]{};

void Variant::init_bindings() {
	// Start from 1 to skip NIL.
	for (int i = 1; i < VARIANT_MAX; i++) {
		from_type_constructor[i] = internal::gdn_interface->get_variant_from_type_constructor((GDNativeVariantType)i);
		to_type_constructor[i] = internal::gdn_interface->get_variant_to_type_constructor((GDNativeVariantType)i);
	}

	StringName::init_bindings();
	String::init_bindings();
	NodePath::init_bindings();
	RID::init_bindings();
	Callable::init_bindings();
	Signal::init_bindings();
	Dictionary::init_bindings();
	Array::init_bindings();
	PackedByteArray::init_bindings();
	PackedInt32Array::init_bindings();
	PackedInt64Array::init_bindings();
	PackedFloat32Array::init_bindings();
	PackedFloat64Array::init_bindings();
	PackedStringArray::init_bindings();
	PackedVector2Array::init_bindings();
	PackedVector3Array::init_bindings();
	PackedColorArray::init_bindings();
}

Variant::Variant() {
	internal::gdn_interface->variant_new_nil(_native_ptr());
}

Variant::Variant(GDNativeConstVariantPtr native_ptr) {
	internal::gdn_interface->variant_new_copy(_native_ptr(), native_ptr);
}

Variant::Variant(const Variant &other) {
	internal::gdn_interface->variant_new_copy(_native_ptr(), other._native_ptr());
}

Variant::Variant(Variant &&other) {
	std::swap(opaque, other.opaque);
}

Variant::Variant(bool v) {
	GDNativeBool encoded;
	PtrToArg<bool>::encode(v, &encoded);
	from_type_constructor[BOOL](_native_ptr(), &encoded);
}

Variant::Variant(int64_t v) {
	GDNativeInt encoded;
	PtrToArg<int64_t>::encode(v, &encoded);
	from_type_constructor[INT](_native_ptr(), &encoded);
}

Variant::Variant(double v) {
	double encoded;
	PtrToArg<double>::encode(v, &encoded);
	from_type_constructor[FLOAT](_native_ptr(), &encoded);
}

Variant::Variant(const String &v) {
	from_type_constructor[STRING](_native_ptr(), v._native_ptr());
}

Variant::Variant(const Vector2 &v) {
	from_type_constructor[VECTOR2](_native_ptr(), (GDNativeTypePtr)&v);
}

Variant::Variant(const Vector2i &v) {
	from_type_constructor[VECTOR2I](_native_ptr(), (GDNativeTypePtr)&v);
}

Variant::Variant(const Rect2 &v) {
	from_type_constructor[RECT2](_native_ptr(), (GDNativeTypePtr)&v);
}

Variant::Variant(const Rect2i &v) {
	from_type_constructor[RECT2I](_native_ptr(), (GDNativeTypePtr)&v);
}

Variant::Variant(const Vector3 &v) {
	from_type_constructor[VECTOR3](_native_ptr(), (GDNativeTypePtr)&v);
}

Variant::Variant(const Vector3i &v) {
	from_type_constructor[VECTOR3I](_native_ptr(), (GDNativeTypePtr)&v);
}

Variant::Variant(const Transform2D &v) {
	from_type_constructor[TRANSFORM2D](_native_ptr(), (GDNativeTypePtr)&v);
}

Variant::Variant(const Vector4 &v) {
	from_type_constructor[VECTOR4](_native_ptr(), (GDNativeTypePtr)&v);
}

Variant::Variant(const Vector4i &v) {
	from_type_constructor[VECTOR4I](_native_ptr(), (GDNativeTypePtr)&v);
}

Variant::Variant(const Plane &v) {
	from_type_constructor[PLANE](_native_ptr(), (GDNativeTypePtr)&v);
}

Variant::Variant(const Quaternion &v) {
	from_type_constructor[QUATERNION](_native_ptr(), (GDNativeTypePtr)&v);
}

Variant::Variant(const godot::AABB &v) {
	from_type_constructor[AABB](_native_ptr(), (GDNativeTypePtr)&v);
}

Variant::Variant(const Basis &v) {
	from_type_constructor[BASIS](_native_ptr(), (GDNativeTypePtr)&v);
}

Variant::Variant(const Transform3D &v) {
	from_type_constructor[TRANSFORM3D](_native_ptr(), (GDNativeTypePtr)&v);
}

Variant::Variant(const Projection &v) {
	from_type_constructor[PROJECTION](_native_ptr(), (GDNativeTypePtr)&v);
}

Variant::Variant(const Color &v) {
	from_type_constructor[COLOR](_native_ptr(), (GDNativeTypePtr)&v);
}

Variant::Variant(const StringName &v) {
	from_type_constructor[STRING_NAME](_native_ptr(), v._native_ptr());
}

Variant::Variant(const NodePath &v) {
	from_type_constructor[NODE_PATH](_native_ptr(), v._native_ptr());
}

Variant::Variant(const godot::RID &v) {
	from_type_constructor[RID](_native_ptr(), v._native_ptr());
}

Variant::Variant(const Object *v) {
	if (v) {
		from_type_constructor[OBJECT](_native_ptr(), const_cast<GodotObject **>(&v->_owner));
	} else {
		GodotObject *nullobject = nullptr;
		from_type_constructor[OBJECT](_native_ptr(), &nullobject);
	}
}

Variant::Variant(const Callable &v) {
	from_type_constructor[CALLABLE](_native_ptr(), v._native_ptr());
}

Variant::Variant(const Signal &v) {
	from_type_constructor[SIGNAL](_native_ptr(), v._native_ptr());
}

Variant::Variant(const Dictionary &v) {
	from_type_constructor[DICTIONARY](_native_ptr(), v._native_ptr());
}

Variant::Variant(const Array &v) {
	from_type_constructor[ARRAY](_native_ptr(), v._native_ptr());
}

Variant::Variant(const PackedByteArray &v) {
	from_type_constructor[PACKED_BYTE_ARRAY](_native_ptr(), v._native_ptr());
}

Variant::Variant(const PackedInt32Array &v) {
	from_type_constructor[PACKED_INT32_ARRAY](_native_ptr(), v._native_ptr());
}

Variant::Variant(const PackedInt64Array &v) {
	from_type_constructor[PACKED_INT64_ARRAY](_native_ptr(), v._native_ptr());
}

Variant::Variant(const PackedFloat32Array &v) {
	from_type_constructor[PACKED_FLOAT32_ARRAY](_native_ptr(), v._native_ptr());
}

Variant::Variant(const PackedFloat64Array &v) {
	from_type_constructor[PACKED_FLOAT64_ARRAY](_native_ptr(), v._native_ptr());
}

Variant::Variant(const PackedStringArray &v) {
	from_type_constructor[PACKED_STRING_ARRAY](_native_ptr(), v._native_ptr());
}

Variant::Variant(const PackedVector2Array &v) {
	from_type_constructor[PACKED_VECTOR2_ARRAY](_native_ptr(), v._native_ptr());
}

Variant::Variant(const PackedVector3Array &v) {
	from_type_constructor[PACKED_VECTOR3_ARRAY](_native_ptr(), v._native_ptr());
}

Variant::Variant(const PackedColorArray &v) {
	from_type_constructor[PACKED_COLOR_ARRAY](_native_ptr(), v._native_ptr());
}

Variant::~Variant() {
	internal::gdn_interface->variant_destroy(_native_ptr());
}

Variant::operator bool() const {
	GDNativeBool result;
	to_type_constructor[BOOL](&result, _native_ptr());
	return PtrToArg<bool>::convert(&result);
}

Variant::operator int64_t() const {
	GDNativeInt result;
	to_type_constructor[INT](&result, _native_ptr());
	return PtrToArg<int64_t>::convert(&result);
}

Variant::operator int32_t() const {
	return static_cast<int32_t>(operator int64_t());
}

Variant::operator uint64_t() const {
	return static_cast<uint64_t>(operator int64_t());
}

Variant::operator uint32_t() const {
	return static_cast<uint32_t>(operator int64_t());
}

Variant::operator double() const {
	double result;
	to_type_constructor[FLOAT](&result, _native_ptr());
	return PtrToArg<double>::convert(&result);
}

Variant::operator float() const {
	return static_cast<float>(operator double());
}

Variant::operator String() const {
	String result;
	to_type_constructor[STRING](result._native_ptr(), _native_ptr());
	return result;
}

Variant::operator Vector2() const {
	Vector2 result;
	to_type_constructor[VECTOR2]((GDNativeTypePtr)&result, _native_ptr());
	return result;
}

Variant::operator Vector2i() const {
	Vector2i result;
	to_type_constructor[VECTOR2I]((GDNativeTypePtr)&result, _native_ptr());
	return result;
}

Variant::operator Rect2() const {
	Rect2 result;
	to_type_constructor[RECT2]((GDNativeTypePtr)&result, _native_ptr());
	return result;
}

Variant::operator Rect2i() const {
	Rect2i result;
	to_type_constructor[RECT2I]((GDNativeTypePtr)&result, _native_ptr());
	return result;
}

Variant::operator Vector3() const {
	Vector3 result;
	to_type_constructor[VECTOR3]((GDNativeTypePtr)&result, _native_ptr());
	return result;
}

Variant::operator Vector3i() const {
	Vector3i result;
	to_type_constructor[VECTOR3I]((GDNativeTypePtr)&result, _native_ptr());
	return result;
}

Variant::operator Transform2D() const {
	Transform2D result;
	to_type_constructor[TRANSFORM2D]((GDNativeTypePtr)&result, _native_ptr());
	return result;
}

Variant::operator Vector4() const {
	Vector4 result;
	to_type_constructor[VECTOR4]((GDNativeTypePtr)&result, _native_ptr());
	return result;
}

Variant::operator Vector4i() const {
	Vector4i result;
	to_type_constructor[VECTOR4I]((GDNativeTypePtr)&result, _native_ptr());
	return result;
}

Variant::operator Plane() const {
	Plane result;
	to_type_constructor[PLANE]((GDNativeTypePtr)&result, _native_ptr());
	return result;
}

Variant::operator Quaternion() const {
	Quaternion result;
	to_type_constructor[QUATERNION]((GDNativeTypePtr)&result, _native_ptr());
	return result;
}

Variant::operator godot::AABB() const {
	godot::AABB result;
	to_type_constructor[AABB]((GDNativeTypePtr)&result, _native_ptr());
	return result;
}

Variant::operator Basis() const {
	Basis result;
	to_type_constructor[BASIS]((GDNativeTypePtr)&result, _native_ptr());
	return result;
}

Variant::operator Transform3D() const {
	Transform3D result;
	to_type_constructor[TRANSFORM3D]((GDNativeTypePtr)&result, _native_ptr());
	return result;
}

Variant::operator Projection() const {
	Projection result;
	to_type_constructor[PROJECTION]((GDNativeTypePtr)&result, _native_ptr());
	return result;
}

Variant::operator Color() const {
	Color result;
	to_type_constructor[COLOR]((GDNativeTypePtr)&result, _native_ptr());
	return result;
}

Variant::operator StringName() const {
	StringName result;
	to_type_constructor[STRING_NAME](result._native_ptr(), _native_ptr());
	return result;
}

Variant::operator NodePath() const {
	NodePath result;
	to_type_constructor[NODE_PATH](result._native_ptr(), _native_ptr());
	return result;
}

Variant::operator godot::RID() const {
	godot::RID result;
	to_type_constructor[RID](result._native_ptr(), _native_ptr());
	return result;
}

Variant::operator Object *() const {
	GodotObject *obj;
	to_type_constructor[OBJECT](&obj, _native_ptr());
	if (obj == nullptr) {
		return nullptr;
	}
	return reinterpret_cast<Object *>(internal::gdn_interface->object_get_instance_binding(obj, internal::token, &Object::___binding_callbacks));
}

Variant::operator Callable() const {
	Callable result;
	to_type_constructor[CALLABLE](result._native_ptr(), _native_ptr());
	return result;
}

Variant::operator Signal() const {
	Signal result;
	to_type_constructor[SIGNAL](result._native_ptr(), _native_ptr());
	return result;
}

Variant::operator Dictionary() const {
	Dictionary result;
	to_type_constructor[DICTIONARY](result._native_ptr(), _native_ptr());
	return result;
}

Variant::operator Array() const {
	Array result;
	to_type_constructor[ARRAY](result._native_ptr(), _native_ptr());
	return result;
}

Variant::operator PackedByteArray() const {
	PackedByteArray result;
	to_type_constructor[PACKED_BYTE_ARRAY](result._native_ptr(), _native_ptr());
	return result;
}

Variant::operator PackedInt32Array() const {
	PackedInt32Array result;
	to_type_constructor[PACKED_INT32_ARRAY](result._native_ptr(), _native_ptr());
	return result;
}

Variant::operator PackedInt64Array() const {
	PackedInt64Array result;
	to_type_constructor[PACKED_INT64_ARRAY](result._native_ptr(), _native_ptr());
	return result;
}

Variant::operator PackedFloat32Array() const {
	PackedFloat32Array result;
	to_type_constructor[PACKED_FLOAT32_ARRAY](result._native_ptr(), _native_ptr());
	return result;
}

Variant::operator PackedFloat64Array() const {
	PackedFloat64Array result;
	to_type_constructor[PACKED_FLOAT64_ARRAY](result._native_ptr(), _native_ptr());
	return result;
}

Variant::operator PackedStringArray() const {
	PackedStringArray result;
	to_type_constructor[PACKED_STRING_ARRAY](result._native_ptr(), _native_ptr());
	return result;
}

Variant::operator PackedVector2Array() const {
	PackedVector2Array result;
	to_type_constructor[PACKED_VECTOR2_ARRAY](result._native_ptr(), _native_ptr());
	return result;
}

Variant::operator PackedVector3Array() const {
	PackedVector3Array result;
	to_type_constructor[PACKED_VECTOR3_ARRAY](result._native_ptr(), _native_ptr());
	return result;
}

Variant::operator PackedColorArray() const {
	PackedColorArray result;
	to_type_constructor[PACKED_COLOR_ARRAY](result._native_ptr(), _native_ptr());
	return result;
}

Variant &Variant::operator=(const Variant &other) {
	clear();
	internal::gdn_interface->variant_new_copy(_native_ptr(), other._native_ptr());
	return *this;
}

Variant &Variant::operator=(Variant &&other) {
	std::swap(opaque, other.opaque);
	return *this;
}

bool Variant::operator==(const Variant &other) const {
	if (get_type() != other.get_type()) {
		return false;
	}
	bool valid = false;
	Variant result;
	evaluate(OP_EQUAL, *this, other, result, valid);
	return result.operator bool();
}

bool Variant::operator!=(const Variant &other) const {
	if (get_type() != other.get_type()) {
		return true;
	}
	bool valid = false;
	Variant result;
	evaluate(OP_NOT_EQUAL, *this, other, result, valid);
	return result.operator bool();
}

bool Variant::operator<(const Variant &other) const {
	if (get_type() != other.get_type()) {
		return get_type() < other.get_type();
	}
	bool valid = false;
	Variant result;
	evaluate(OP_LESS, *this, other, result, valid);
	return result.operator bool();
}

void Variant::call(const StringName &method, const Variant **args, int argcount, Variant &r_ret, GDNativeCallError &r_error) {
	internal::gdn_interface->variant_call(_native_ptr(), method._native_ptr(), reinterpret_cast<GDNativeConstVariantPtr *>(args), argcount, r_ret._native_ptr(), &r_error);
}

void Variant::call_static(Variant::Type type, const StringName &method, const Variant **args, int argcount, Variant &r_ret, GDNativeCallError &r_error) {
	internal::gdn_interface->variant_call_static(static_cast<GDNativeVariantType>(type), method._native_ptr(), reinterpret_cast<GDNativeConstVariantPtr *>(args), argcount, r_ret._native_ptr(), &r_error);
}

void Variant::evaluate(const Operator &op, const Variant &a, const Variant &b, Variant &r_ret, bool &r_valid) {
	GDNativeBool valid;
	internal::gdn_interface->variant_evaluate(static_cast<GDNativeVariantOperator>(op), a._native_ptr(), b._native_ptr(), r_ret._native_ptr(), &valid);
	r_valid = PtrToArg<bool>::convert(&valid);
}

void Variant::set(const Variant &key, const Variant &value, bool *r_valid) {
	GDNativeBool valid;
	internal::gdn_interface->variant_set(_native_ptr(), key._native_ptr(), value._native_ptr(), &valid);
	if (r_valid) {
		*r_valid = PtrToArg<bool>::convert(&valid);
	}
}

void Variant::set_named(const StringName &name, const Variant &value, bool &r_valid) {
	GDNativeBool valid;
	internal::gdn_interface->variant_set_named(_native_ptr(), name._native_ptr(), value._native_ptr(), &valid);
	r_valid = PtrToArg<bool>::convert(&valid);
}

void Variant::set_indexed(int64_t index, const Variant &value, bool &r_valid, bool &r_oob) {
	GDNativeBool valid, oob;
	internal::gdn_interface->variant_set_indexed(_native_ptr(), index, value._native_ptr(), &valid, &oob);
	r_valid = PtrToArg<bool>::convert(&valid);
	r_oob = PtrToArg<bool>::convert(&oob);
}

void Variant::set_keyed(const Variant &key, const Variant &value, bool &r_valid) {
	GDNativeBool valid;
	internal::gdn_interface->variant_set_keyed(_native_ptr(), key._native_ptr(), value._native_ptr(), &valid);
	r_valid = PtrToArg<bool>::convert(&valid);
}

Variant Variant::get(const Variant &key, bool *r_valid) const {
	Variant result;
	GDNativeBool valid;
	internal::gdn_interface->variant_get(_native_ptr(), key._native_ptr(), result._native_ptr(), &valid);
	if (r_valid) {
		*r_valid = PtrToArg<bool>::convert(&valid);
	}
	return result;
}

Variant Variant::get_named(const StringName &name, bool &r_valid) const {
	Variant result;
	GDNativeBool valid;
	internal::gdn_interface->variant_get_named(_native_ptr(), name._native_ptr(), result._native_ptr(), &valid);
	r_valid = PtrToArg<bool>::convert(&valid);
	return result;
}

Variant Variant::get_indexed(int64_t index, bool &r_valid, bool &r_oob) const {
	Variant result;
	GDNativeBool valid;
	GDNativeBool oob;
	internal::gdn_interface->variant_get_indexed(_native_ptr(), index, result._native_ptr(), &valid, &oob);
	r_valid = PtrToArg<bool>::convert(&valid);
	r_oob = PtrToArg<bool>::convert(&oob);
	return result;
}

Variant Variant::get_keyed(const Variant &key, bool &r_valid) const {
	Variant result;
	GDNativeBool valid;
	internal::gdn_interface->variant_get_keyed(_native_ptr(), key._native_ptr(), result._native_ptr(), &valid);
	r_valid = PtrToArg<bool>::convert(&valid);
	return result;
}

bool Variant::in(const Variant &index, bool *r_valid) const {
	Variant result;
	bool valid;
	evaluate(OP_IN, *this, index, result, valid);
	if (r_valid) {
		*r_valid = valid;
	}
	return result.operator bool();
}

bool Variant::iter_init(Variant &r_iter, bool &r_valid) const {
	GDNativeBool valid;
	internal::gdn_interface->variant_iter_init(_native_ptr(), r_iter._native_ptr(), &valid);
	return PtrToArg<bool>::convert(&valid);
}

bool Variant::iter_next(Variant &r_iter, bool &r_valid) const {
	GDNativeBool valid;
	internal::gdn_interface->variant_iter_next(_native_ptr(), r_iter._native_ptr(), &valid);
	return PtrToArg<bool>::convert(&valid);
}

Variant Variant::iter_get(const Variant &r_iter, bool &r_valid) const {
	Variant result;
	GDNativeBool valid;
	internal::gdn_interface->variant_iter_get(_native_ptr(), r_iter._native_ptr(), result._native_ptr(), &valid);
	r_valid = PtrToArg<bool>::convert(&valid);
	return result;
}

Variant::Type Variant::get_type() const {
	return static_cast<Variant::Type>(internal::gdn_interface->variant_get_type(_native_ptr()));
}

bool Variant::has_method(const StringName &method) const {
	GDNativeBool has = internal::gdn_interface->variant_has_method(_native_ptr(), method._native_ptr());
	return PtrToArg<bool>::convert(&has);
}

bool Variant::has_key(const Variant &key, bool *r_valid) const {
	GDNativeBool valid;
	GDNativeBool has = internal::gdn_interface->variant_has_key(_native_ptr(), key._native_ptr(), &valid);
	if (r_valid) {
		*r_valid = PtrToArg<bool>::convert(&valid);
	}
	return PtrToArg<bool>::convert(&has);
}

bool Variant::has_member(Variant::Type type, const StringName &member) {
	GDNativeBool has = internal::gdn_interface->variant_has_member(static_cast<GDNativeVariantType>(type), member._native_ptr());
	return PtrToArg<bool>::convert(&has);
}

uint32_t Variant::hash() const {
	GDNativeInt hash = internal::gdn_interface->variant_hash(_native_ptr());
	return PtrToArg<uint32_t>::convert(&hash);
}

uint32_t Variant::recursive_hash(int recursion_count) const {
	GDNativeInt hash = internal::gdn_interface->variant_recursive_hash(_native_ptr(), recursion_count);
	return PtrToArg<uint32_t>::convert(&hash);
}

bool Variant::hash_compare(const Variant &variant) const {
	GDNativeBool compare = internal::gdn_interface->variant_hash_compare(_native_ptr(), variant._native_ptr());
	return PtrToArg<bool>::convert(&compare);
}

bool Variant::booleanize() const {
	GDNativeBool booleanized = internal::gdn_interface->variant_booleanize(_native_ptr());
	return PtrToArg<bool>::convert(&booleanized);
}

String Variant::stringify() const {
	String result;
	internal::gdn_interface->variant_stringify(_native_ptr(), result._native_ptr());
	return result;
}

Variant Variant::duplicate(bool deep) const {
	Variant result;
	GDNativeBool _deep;
	PtrToArg<bool>::encode(deep, &_deep);
	internal::gdn_interface->variant_duplicate(_native_ptr(), result._native_ptr(), _deep);
	return result;
}

String Variant::get_type_name(Variant::Type type) {
	String result;
	internal::gdn_interface->variant_get_type_name(static_cast<GDNativeVariantType>(type), result._native_ptr());
	return result;
}

bool Variant::can_convert(Variant::Type from, Variant::Type to) {
	GDNativeBool can;
	internal::gdn_interface->variant_can_convert(static_cast<GDNativeVariantType>(from), static_cast<GDNativeVariantType>(to));
	return PtrToArg<bool>::convert(&can);
}

bool Variant::can_convert_strict(Variant::Type from, Variant::Type to) {
	GDNativeBool can;
	internal::gdn_interface->variant_can_convert_strict(static_cast<GDNativeVariantType>(from), static_cast<GDNativeVariantType>(to));
	return PtrToArg<bool>::convert(&can);
}

void Variant::clear() {
	static const bool needs_deinit[Variant::VARIANT_MAX] = {
		false, // NIL,
		false, // BOOL,
		false, // INT,
		false, // FLOAT,
		true, // STRING,
		false, // VECTOR2,
		false, // VECTOR2I,
		false, // RECT2,
		false, // RECT2I,
		false, // VECTOR3,
		false, // VECTOR3I,
		true, // TRANSFORM2D,
		false, // VECTOR4,
		false, // VECTOR4I,
		false, // PLANE,
		false, // QUATERNION,
		true, // AABB,
		true, // BASIS,
		true, // TRANSFORM3D,
		true, // PROJECTION,

		// misc types
		false, // COLOR,
		true, // STRING_NAME,
		true, // NODE_PATH,
		false, // RID,
		true, // OBJECT,
		true, // CALLABLE,
		true, // SIGNAL,
		true, // DICTIONARY,
		true, // ARRAY,

		// typed arrays
		true, // PACKED_BYTE_ARRAY,
		true, // PACKED_INT32_ARRAY,
		true, // PACKED_INT64_ARRAY,
		true, // PACKED_FLOAT32_ARRAY,
		true, // PACKED_FLOAT64_ARRAY,
		true, // PACKED_STRING_ARRAY,
		true, // PACKED_VECTOR2_ARRAY,
		true, // PACKED_VECTOR3_ARRAY,
		true, // PACKED_COLOR_ARRAY,
	};

	if (unlikely(needs_deinit[get_type()])) { // Make it fast for types that don't need deinit.
		internal::gdn_interface->variant_destroy(_native_ptr());
	}
	internal::gdn_interface->variant_new_nil(_native_ptr());
}

} // namespace godot
