// Geometry Library
//
// Copyright Barend Gehrels, Geodan Holding B.V. Amsterdam, the Netherlands.
// Copyright Bruno Lalande 2008
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef _DOXYGEN_MAINPAGE_HPP
#define _DOXYGEN_MAINPAGE_HPP


/*!
\mainpage Geometry Library

\section header Geometry Library

This Geometry Library is considered to be proposed to Boost,
and is prepared for Boost until a certain point.
It is not part of Boost.

<em>Copyright © 1995-2008 <b>Barend Gehrels</b>, Geodan Holding B.V. Amsterdam, the Netherlands.\n
Copyright © 2008 <b>Bruno Lalande</b>, Paris, France.\n
Distributed under the Boost Software License, Version 1.0.\n
(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
</em>

\section intro Introduction
The Geometry Library provides a generic implementation of geometry
algorithms, with the ability to work with any user-defined type of
points in any number of dimensions. It also proposes some point
classes for those who don't have any already defined point type, and
provides classes like polygon or box for more complex operations.

The algorithms include some well-known and often needed algorithms as
point-in-polygon, polygon area, point-to-point distance, point-to-line distance, line clipping and
polygon clipping. The algorithms work, of course, on the geometry
classes provided by the library, but they also work on geometry classes defined by the library
user.

The library follows conventions used in the std:: library and in the boost:: libraries. It also
follows, where possible, the OGC names and conventions. OGC is the Open Geospatial Consortium,
the standardization committee on GIS (Geographical Information Systems). OGC geometries are used
in many environments, among others in databases (Oracle, MySQL, PostgreSQL). OGC specifies a library
based on inheritance, as opposed to this library, which is a template library where data classes are
strictly separated from the algorithms. Therefore it is not an OGC implementation (but an
OGC implementation could be built with this library).

\section platforms Platforms

The library currently compiles successfully on the following platforms:
- MS Visual Studio 2008 (Express Edition)
- MS Visual Studio 2005 (Express Edition)
- gcc version 3.4
- gcc version 4.1
- gcc version 4.2

It doesn't compile on the following platform:
- MS Visual Studio 2003 (some compiler issues)
- MS Visual Studio 6 (because of nested templates)

\section history History
Geodan started in 1995 with a Geographic Library, called geolib. Since then hundreds of projects have
been done using this geolib, and the geolib have been extended to fit the needs of its users. Geolib
can be used in different environments: in Windows applications, as a DLL (ggl32.dll), in
Web Map Servers (SclMapServer), Web Feature Servers or more specific programs.

In 2007/2008 the Geometry part has been revised and completely templatized. In 2008 Bruno Lalande,
already a Boost contributor, joined and helped to make the library even more generic
and to define clear concepts.
The Geometry Library is Open Source and will be proposed to the Boost community.

This is preview 3.

The library can be downloaded on the \ref download "Download page"
*/





#endif // _DOXYGEN_MAINPAGE_HPP
