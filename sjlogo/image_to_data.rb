require 'set'

def get_dimensions(path)
  s = `identify #{path}`
  s.split(/\s+/)[2].split('x').map(&:to_i)
end

def each_pixel(bytes)
  unless block_given?
    return to_enum(:each_pixel, bytes)
  end
  bytes.scan(/.../) do |pixel|
    colors = pixel.unpack("CCC")
    yield colors
  end
end

def extract_palette(bytes)
  palette = Set.new
  each_pixel(bytes) do |pixel|
    palette << pixel
  end
  palette.to_a
end

def index_image(palette, bytes)
  each_pixel(bytes).map { |pixel|
    palette.index(pixel)
  }
end

def as_curly_brace_triple(pixel)
  "{#{pixel.map(&:to_s).join(",")}}"
end

def as_curly_brace_triples(pixels)
  pixels.map {|pixel|
    as_curly_brace_triple(pixel)
  }.join(",")
end

def image_to_data(in_path)
  w, h = get_dimensions(in_path)
  system("stream #{in_path} tmp.raw")
  File.open('tmp.raw', 'rb') do |file|
    bytes = file.read
    palette = extract_palette(bytes)
    indexed = index_image(palette, bytes)
    return <<-C
int palette[][3] = {#{as_curly_brace_triples(palette)}};
char image[] = {#{indexed.map(&:to_s).join(",")}};
#define STRIDE #{w}
    C
  end
end

if __FILE__ == $0
  puts image_to_data(ARGV[0])
end

