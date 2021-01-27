#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <stdexcept>
#include "wavefront_obj.h"

namespace {

using double2 = wavefront_obj_t::double2;
using double3 = wavefront_obj_t::double3;

// normalize double2 or double3 into unit vector if it is nonzero.
#ifdef _MSC_VER
template<class T, int S>
std::array<T, S> normalize( std::array<T, S> u ) {
    T l = T( 0 );
    for ( std::size_t i = 0; i < S; ++i )
        l += u[i] * u[i];

    //skip if zero
    if ( l == T( 0 ) )
        return u;

    l = std::sqrt( l );
    for ( std::size_t i = 0; i < S; ++i )
        u[i] /= l;

    return u;
}
#endif

#ifdef __APPLE__
    template<typename T, unsigned long S>
    std::array<T, S> normalize( std::array<T, S> u ) {
        T l = T( 0 );
        for ( std::size_t i = 0; i < S; ++i )
            l += u[i] * u[i];

        //skip if zero
        if ( l == T( 0 ) )
            return u;

        l = std::sqrt( l );
        for ( std::size_t i = 0; i < S; ++i )
            u[i] /= l;

        return u;
    }
#endif

//Given three vertices forming a triangle, compute the normal direction of its face
double3 compute_face_normal( double3 &v0, double3 &v1, double3 &v2 ) {
    double3 a, b, n;

    for ( int i = 0; i < 3; ++i ) {
        a[i] = v1[i] - v0[i];
        b[i] = v2[i] - v0[i];
    }

    n[0] = a[1] * b[2] - a[2] * b[1];
    n[1] = a[2] * b[0] - a[0] * b[2];
    n[2] = a[0] * b[1] - a[1] * b[0];

    return normalize( n );
}

//Given a list (represented by a pair of iterators) of vertices, compute axis-aligned bounding box (AABB).
template<class IterT>
std::pair<double3, double3> compute_aabb( IterT vert_begin, IterT vert_end ) {
    std::pair<double3, double3> aabb{ double3{0, 0, 0}, double3{0, 0, 0} };

    for( ; vert_begin != vert_end; ++vert_begin ) {
        auto &vert = *vert_begin;

        for ( int i = 0; i < 3; ++i ) {
            aabb.first[i] = std::min( aabb.first[i], vert[i] );
            aabb.second[i] = std::max( aabb.second[i], vert[i] );
        }
    }

    return aabb;
}

}

wavefront_obj_t::wavefront_obj_t( char *path ) {
    is_flat = true;

    std::string line;
    std::istringstream line_stream, item_stream;

    std::ifstream file( path );
    if ( !file )
        throw std::runtime_error( "Cannot open file." );

    while ( std::getline( file, line ) ) {
        // strip off comments and blank lines
        if ( line[0] == '#' || line.size() == 0 )
            continue;

        // parse line
        line_stream.clear();
        line_stream.str( line );

        std::string mode;
        line_stream >> mode;
        if ( mode == "v" ) {
            double x, y, z;
            line_stream >> x >> y >> z;
            vertices.push_back( double3{ x, y, z } );
        } else if ( mode == "vn" ) {
            double x, y, z;
            line_stream >> x >> y >> z;
            normals.push_back( normalize( double3{ x, y, z } ) );
        } else if ( mode == "vt" ) {
            double u, v;
            line_stream >> u >> v;
            texcoords.push_back( double2{u, v} );
        } else if ( mode == "f" ) {
            face_t face;
            std::memset( &face, 0, sizeof( face_t ) );
            face.idx_begin = vertex_indices.size();

            std::string item;
            while ( line_stream >> item ) {
                item_stream.clear();
                item_stream.str( item );

                int v = 0, t = 0, n = 0;
				do {
					item_stream >> v;
					char c;
					if (!(bool(item_stream >> c) && c == '/'))
						continue;
					if (!(item_stream >> t))
						item_stream.clear();
					if (!(bool(item_stream >> c) && c == '/'))
						continue;
					if (!(item_stream >> n))
						item_stream.clear();
				} while (false);

                vertex_indices.push_back( v - 1 );
                texcoord_indices.push_back( t - 1 );
                normal_indices.push_back( n - 1 );
                ++face.count;

                if ( n )
                    is_flat = false;
            }
            if ( face.count > 2 ) {
                face.normal = compute_face_normal(
                                  vertices[vertex_indices[face.idx_begin]],
                                  vertices[vertex_indices[face.idx_begin + 1]],
                                  vertices[vertex_indices[face.idx_begin + 2]]
                              );
            }

            faces.push_back( face );
        } else if ( mode == "g" ) { // group
        } else if ( mode == "s" ) { // smoothing group
        } else if ( mode == "u" ) { // material line
        } else {
            std::cerr << "Warning: unsupported Wavefront OBJ option: " << mode << "\n";
        }
    }

    aabb = compute_aabb( std::begin( vertices ), std::end( vertices ) );
}


//------------------------------------------------------------------------------
// Draw object which is read from file
void wavefront_obj_t::draw() {
    for ( std::size_t f = 0; f < faces.size(); f++ ) {
        face_t &face = faces[f];
        glBegin( gl_primitive_mode );
        for ( std::size_t v = 0; v < face.count; v++ ) {
            int vi = face.idx_begin + v;
            int i;
            if ( is_flat ) {
                if ( v == 0 ) {
                    glNormal3dv( face.normal.data() );
                }
            } else if ( ( i = normal_indices[vi] ) >= 0 ) {
                glNormal3dv( normals[i].data() );
            }
            if ( ( i = texcoord_indices[vi] ) >= 0 ) {
                glTexCoord2dv( texcoords[i].data() );
            }
            if ( ( i = vertex_indices[vi] ) >= 0 ) {
                glVertex3dv( vertices[i].data() );
            }
        }
        glEnd();
    }
}
