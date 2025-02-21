project(
	'hyprsymbol',
	'c',
	meson_version : '>= 1.1.0',
	version : '1.0.0',
	default_options : [
		'c_args=-D_GNU_SOURCE',
		'c_std=c99', # -std=c99
		'debug=true', # -g
		'optimization=0', # -O0
		'warning_level=3', # -Wall -Wextra -Wpedantic
		'b_sanitize=address,undefined',
	],
)

public_headers = [
	include_directories('include')
]

private_headers = [
	include_directories('src')
]

executable(
    'hyprsymbol',
    sources : [ 
		'lib/xdg-shell.c',
		'lib/wlr-layer-shell-unstable-v1.c',

		'src/shm.c',
		'src/hyprsymbol.c',
		'src/renderer.c',

		'src/main.c'
	],
	include_directories: public_headers + private_headers,
    dependencies : [ dependency('pangocairo'), dependency('cairo'), dependency('wayland-client') ],
    install : true,
)

# Add tests here
# test('test_name', main, args: [ 'this', 'is', 'argv' ])
# ...