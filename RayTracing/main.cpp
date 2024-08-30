#include "color.h"
#include "vec3.h"
#include "ray.h"

#include <iostream>
#include <format>

#include <fstream>

using namespace std;

Double hit_sphere(const point3& center, double radius, const ray& r)
{
	vec3 oc = center - r.origin();
	Double a = r.direction().length_squared();
	Double h = dot(r.direction(), oc);
	Double c = oc.length_squared() - radius * radius;
	Double discriminant = h*h - a*c;
	
	if (discriminant < 0)
	{
		return -1.0;
	}
	else
	{
		return (h - sqrt(discriminant)) /  a;
	}
}

color ray_color(const ray& r)
{
	Double t = hit_sphere(point3(0, 0, -1), 0.5, r);
	if (t > 0.0)
	{
		vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));

		vec3 LightDir = vec3(0.0, 0.0, -1.0);
		Double Intensity = dot(N, -LightDir);

		return color(1.0 * Intensity, 1.0 * Intensity, 1.0 * Intensity);
	}

	vec3 unit_direction = unit_vector(r.direction());
	Double a = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - a)* color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main()
{

	// Image
	Double aspect_ratio = 16.0 / 9.0;
	int image_width = 1920;

	// Calculate the image height, and ensure that it's at least 1.
	int image_height = static_cast<int>(image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height;

	// Camera
	Double focal_length = 1.0;
	Double viewport_height = 2.0;
	Double viewport_width = viewport_height * (static_cast<Double>(image_width) / image_height);
	point3 camera_center = point3(0, 0, 0);

	// Calculate the vectors across the horizontal and down the vertical viewport edges.
	vec3 viewport_u = vec3(viewport_width, 0, 0);
	vec3 viewport_v = vec3(0, -viewport_height, 0);

	// Calculate the location of the upper left pixel.
	vec3 pixel_delta_u = viewport_u / image_width;
	vec3 pixel_delta_v = viewport_v / image_height;

	// Calculate the location of upper left pixel.
	vec3 viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
	vec3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

	// Render
	cout << format("P3\n{} {}\n255\n", image_width, image_height);

	for (int j = 0; j < image_height; ++j)
	{
		clog << format("\rScanlines remaining: {} ", (image_height - j)) << flush;
		for (int i = 0; i < image_width; ++i)
		{
			point3 pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
			vec3 ray_direction = pixel_center - camera_center;
			ray r(camera_center, ray_direction);

			color pixel_color = ray_color(r);
			write_color(std::cout, pixel_color);
		}	
	}

	std::clog << "\rDone.				\n";
}