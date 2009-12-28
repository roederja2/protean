//  (C) Copyright Johan Ditmar, Karel Hruda, Paul O'Neill & Luke Stedman 2009.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef PROTEAN_OBJECT_FACTORY_HPP
#define PROTEAN_OBJECT_FACTORY_HPP

#include <protean/config.hpp>
#include <protean/variant_error.hpp>
#include <protean/object.hpp>
#include <protean/handle.hpp>

#include <boost/function.hpp>

#include <string>
#include <map>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif

namespace protean {

    template<typename T> class handle;

    class PROTEAN_DLLEXPORT object_factory
    {
    public:
        typedef boost::function<handle<object>()> create_fn_t;
        typedef std::map<std::string, create_fn_t> instance_map_t;

    public:
        void initialise();
        void shutdown();

        template<typename TYPE>
        void register_object(const std::string& name);

        handle<object> create_instance(const std::string& name);

    private:
        void insert(const std::string& class_name, const create_fn_t& fn);
        instance_map_t m_instance_map;
    };

    template<class T>
    void object_factory::register_object(const std::string& name)
    {
        std::string class_name(name);
        insert(class_name, &handle<object>::create<T>);
    }
} // namespace protean

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif // PROTEAN_OBJECT_FACTORY_HPP
