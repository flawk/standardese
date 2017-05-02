// Copyright (C) 2016-2017 Jonathan Müller <jonathanmueller.dev@gmail.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level directory of this distribution.

#include <standardese/markup/paragraph.hpp>

#include <catch.hpp>

#include <standardese/markup/generator.hpp>

using namespace standardese::markup;

TEST_CASE("paragraph", "[markup]")
{
    auto html = R"(<p id="standardese-foo">a<em>b</em><code><em>c</em>d</code></p>
)";

    paragraph::builder builder(block_id("foo"));
    builder.add_child(text::build("a"));
    builder.add_child(emphasis::build("b"));
    builder.add_child(
        code::builder().add_child(emphasis::build("c")).add_child(text::build("d")).finish());
    REQUIRE(as_html(*builder.finish()) == html);
}
