#!/bin/bash
# Module structure's creator. Syntax: generate_module.sh <module_name>

if [ $# -eq 0 ]; then
  echo "Syntax: generate_module.sh module_name"
  exit 1
fi

#Module name must be defined!

#Дисковые имена - с подчёркиванием, как_в_параметре
#Имена классов - CaseSensitive

# to_lower
module_name=$1
declare -l module_name
module_name=$module_name

echo $module_name
if [[ ! "$module_name" == [a-z]* ]]; then
  echo "Wrong module name!"
  exit 5
fi

# ToCamelStyle
ModuleName=${module_name//'_'/' '}
ModuleName=($ModuleName)
ModuleName="${ModuleName[@]^}"
ModuleName=${ModuleName//' '/}

#Module is 'so'
module_format="so"

template_dir=$(pwd)

cd ..   #/Modules

#Create main Module dir

if [ -d $module_name ]; then   #КАТАЛОГ С ИМЕНЕМ [module_name] УЖЕ СУЩЕСТВУЕТ!
  echo "Directory [$module_name] already exists! Remove it manually!"
  exit 3
else
  mkdir $module_name
  if [ ! -d $module_name ]; then
    echo "Can't create directory $module_name!"
    exit 4
  fi
fi

echo "$module_name\ module directory has been created!"

cd "$module_name"
module_dir=$(pwd)

# Name templates
search_pattern="\[name\]"
Search_pattern="\[Name\]"
SEARCH_PATTERN="\[NAME\]"
new_pattern=$module_name
NewPattern=${ModuleName}
NEWPATTERN=${new_pattern^^}
template_date="\[create_date\]"
current_date="$(date +'%d.%m.%Y')"


######### Create <include> dir
curr_dir=include
if [ ! -d "$curr_dir" ]; then
  mkdir "$curr_dir"
  if [ ! -d "$curr_dir" ]; then
    echo "Can't create directory $curr_dir!"
    exit 6
  fi
  echo "/$curr_dir created!"
else
  echo "/$curr_dir already exists!"
fi

## Create header file
cd "$curr_dir"

input_header="$template_dir/include/name.h"
output_header="$(pwd)/$module_name.h"

sed -e s/$template_date/$current_date/g \
    -e s/$Search_pattern/$NewPattern/g \
    -e s/$SEARCH_PATTERN/$NEWPATTERN/g \
     <$input_header >$output_header

if [ ! -f "$output_header" ]; then
  echo  "$output_header file hasn't been created!"
  exit 4
fi
echo  "$output_header file has been created!"


cd ..   #up to Module dir

######### Create <src> dir
curr_dir=src
if [ ! -d "$curr_dir" ]; then
  mkdir "$curr_dir"
  if [ ! -d "$curr_dir" ]; then
    echo "Can't create directory $curr_dir!"
    exit 6
  fi
  echo "/$curr_dir created!"
else
  echo "/$curr_dir already exists!"
fi

## Create source file
cd "$curr_dir"

input_cpp="$template_dir/src/name.cpp"
output_cpp="$(pwd)/$module_name.cpp"

sed -e s/$template_date/$current_date/g \
    -e s/$Search_pattern/$NewPattern/g \
    -e s/$search_pattern/$new_pattern/g \
     <$input_cpp >$output_cpp

if [ ! -f "$output_cpp" ]; then
  echo  "$output_cpp file hasn't been created!"
  exit 4
fi
echo  "$output_cpp file has been created!"

cd ..   #up to Module dir

######### Create <lib> dir
#curr_dir=lib
#if [ ! -d "$curr_dir" ]; then
#  mkdir "$curr_dir"
#  if [ ! -d "$curr_dir" ]; then
#    echo "Can't create directory $curr_dir!"
#    exit 6
#  fi
#  echo "/$curr_dir created!"
#else
#  echo "/$curr_dir already exists!"
#fi


#Create .pro file

input_pro="$template_dir/name.pro"
output_pro="$module_dir/$module_name.pro"

PluginStr="CONFIG += plugin"
TargetPluginStr="$PluginStr"

sed -e s/$search_pattern/$new_pattern/g \
    -e s/"$PluginStr"/"$TargetPluginStr"/g \
    <$input_pro >$output_pro

if [ ! -f "$output_pro" ]; then
  echo  "$output_pro pro-file hasn't been create!"
  exit 3
fi
echo  "$output_pro file has been created!"

#Create CMake file

shared="SHARED "

input_cm="$template_dir/CMakeLists.txt"
output_cm="$module_dir/CMakeLists.txt"

sed -e s/$search_pattern/$new_pattern/g \
    -e s/$target_pattern/"##$target_pattern"/g \
    -e s/'add_library(${module_NAME} '/'add_library(${module_NAME} '"$shared"/g \
    <$input_cm >$output_cm
    
if [ ! -f "$output_cm" ]; then
  echo  "$output_cm file hasn't been created!"
  exit 4
fi
echo  "$output_cm file has been created!"

input_build="$template_dir/builder.sh"
output_build="$module_dir/builder.sh"

TemplateFormat="\[shared\]"
sed -e s/$search_pattern/$new_pattern/g \
    -e s/$TemplateFormat/$module_format/g \
    <$input_build >$output_build

chmod +x $output_build

echo "Done!"

exit 0

