#!/usr/bin/python3
import sys
from lxml import html
from inflection import underscore
import requests
import inspect
from dataclasses import dataclass
from typing import List, Optional


@dataclass
class Instruction:
    group: str
    name: str
    specialized_name: Optional[str]
    word_count: int
    opcode: int
    is_word_count_variable: bool
    format: List[str]

    def get_specialized_name(self):
        if self.specialized_name:
            return self.specialized_name
        return self.name

    def get_enum_name(self, specialized_name_override):
        target = self.name
        if specialized_name_override and self.specialized_name is not None:
            target = self.specialized_name
        return underscore(target).upper()

    def __str__(self):
        if self.specialized_name is not None:
            return f"[{self.group}] {self.name} " + \
                   f"({self.specialized_name}) #{self.word_count}" + \
                   f"{' + variable' if self.is_word_count_variable else ''}"
        return f"[{self.group}] {self.name} " + \
               f"#{self.word_count}" + \
               f"{' + variable' if self.is_word_count_variable else ''}"

    def __repr__(self):
        return str(self) + "\n"


class Scraper:
    def __init__(self):
        self.instructions = []

    def flush(self, output_path):
        instruction_list = "#define ENUMERATE_SPIRV_OPCODES(o) \\\n"

        for i in range(len(self.instructions)):
            instruction = self.instructions[i]

            footer = "\\\n"
            if i == len(self.instructions) - 1:
                footer = "\n"

            instruction_list += f'    o({instruction.get_enum_name(True)}, ' + \
                f'"{instruction.get_specialized_name()}", ' + \
                f'{instruction.word_count}, ' + \
                f'{instruction.opcode}, ' + \
                f'{"true" if instruction.is_word_count_variable else "false" } ) ' + footer

        body = f"{instruction_list}"

        file_contents = f"#pragma once\n\n{body}\n"
        with open(output_path, "w") as f:
            f.write(file_contents)

    def scrape_magic_number(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_source_languages(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_execution_models(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_addressing_models(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_memory_models(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_execution_modes(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_storage_classes(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_image_dimensionality(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_sampler_addressing_modes(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_sampler_filter_modes(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_image_formats(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_image_channel_orders(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_image_channel_data_types(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_image_operand_masks(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_fp_fast_math_modes(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_fp_rounding_modes(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_linkage_types(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_access_qualifiers(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_function_parameter_attributes(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_decorations(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_builtin_decorations(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_selection_control_masks(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_loop_control_masks(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_function_control_masks(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_memory_semantics(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_memory_operands(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_scopes(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_group_operations(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_kernel_enqueue_flags(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_kernel_profiling_info_masks(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_capabilities(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_reserved_ray_flags(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_reserved_ray_query_intersections(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_reserved_ray_query_committed_types(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_reserved_ray_query_canditate_types(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_reserved_fragment_shading_rates(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_reserved_fp_denorm_modes(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_reserved_fp_operation_modes(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_quantization_modes(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_overflow_modes(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_packed_vector_format(self, element):
        print(f"Unimplemented function {inspect.stack()[0][3]}")

    def scrape_instructions(self, element):
        instruction_body = element[-1]
        if instruction_body.find('h3[@id="_instructions_3"]') is None:
            raise Exception("Invalid page format")

        instruction_groups = instruction_body.findall('div[@class="sect3"]')
        for group in instruction_groups:
            group_name = group.find("h4").find("a").get("id")
            instructions = group.findall("table")
            for instruction in instructions:
                instruction = instruction.find("tbody")
                rows = instruction.findall("tr")

                # Get name (and possibly specialized name).
                names = rows[0].find("td").find('p[@class="tableblock"]').find("strong").text.split()
                name = names[0]
                specialized_name = None
                if len(names) > 1:
                    # Names are either of the form "xxx" or of the form "xxx (yyy)", where the perentheses
                    # contain a more specific name.
                    specialized_name = names[1][1:-1]

                # get word count
                data_row = rows[1]
                columns = data_row.findall("td")

                word_count = columns[0].find("p").text
                variable_word_count = False
                if "+ variable" in word_count:
                    # Word count is either of the form "xxx" or "xxx + variable", where xxx is a number.
                    variable_word_count = True
                    index = word_count.index("+ variable")
                    word_count = word_count[:index]
                word_count = int(word_count, 0)

                # Get opcode value.
                opcode = int(columns[1].find("p").text, 0)

                # Collect instruction format.
                format = []
                for argument in columns:
                    format.append(argument.find("p").text)
                instruction = Instruction(group_name, name, specialized_name,
                                          word_count, opcode, variable_word_count,
                                          format)
                self.instructions.append(instruction)
        print(f"Scraped {len(self.instructions)} instructions")


if len(sys.argv) != 2:
    print("spirv_scrape.py [output path]")
    sys.exit(1)

# get page
page = None
try:
    page = requests.get("https://registry.khronos.org/SPIR-V/specs/unified1/SPIRV.html")
except Exception:
    print("Could not get page")
    sys.exit(0)

# parse sections
tree = html.fromstring(page.content)
outer_sections = tree.xpath('//div[@id="content"]//div[@class="sect1"]')
binary_form_outer_section = outer_sections[2]
if binary_form_outer_section.find("h2").get("id") != "_binary_form":
    print("Invalid page format")
    sys.exit(1)

scraper = Scraper()
binary_form_outer_section = binary_form_outer_section.find('div[@class="sectionbody"]')
scraper.scrape_magic_number(binary_form_outer_section)
scraper.scrape_source_languages(binary_form_outer_section)
scraper.scrape_execution_models(binary_form_outer_section)
scraper.scrape_addressing_models(binary_form_outer_section)
scraper.scrape_memory_models(binary_form_outer_section)
scraper.scrape_execution_modes(binary_form_outer_section)
scraper.scrape_storage_classes(binary_form_outer_section)
scraper.scrape_image_dimensionality(binary_form_outer_section)
scraper.scrape_sampler_addressing_modes(binary_form_outer_section)
scraper.scrape_sampler_filter_modes(binary_form_outer_section)
scraper.scrape_image_formats(binary_form_outer_section)
scraper.scrape_image_channel_orders(binary_form_outer_section)
scraper.scrape_image_channel_data_types(binary_form_outer_section)
scraper.scrape_image_operand_masks(binary_form_outer_section)
scraper.scrape_fp_fast_math_modes(binary_form_outer_section)
scraper.scrape_fp_rounding_modes(binary_form_outer_section)
scraper.scrape_linkage_types(binary_form_outer_section)
scraper.scrape_access_qualifiers(binary_form_outer_section)
scraper.scrape_function_parameter_attributes(binary_form_outer_section)
scraper.scrape_decorations(binary_form_outer_section)
scraper.scrape_builtin_decorations(binary_form_outer_section)
scraper.scrape_selection_control_masks(binary_form_outer_section)
scraper.scrape_loop_control_masks(binary_form_outer_section)
scraper.scrape_function_control_masks(binary_form_outer_section)
scraper.scrape_memory_semantics(binary_form_outer_section)
scraper.scrape_memory_operands(binary_form_outer_section)
scraper.scrape_scopes(binary_form_outer_section)
scraper.scrape_group_operations(binary_form_outer_section)
scraper.scrape_kernel_enqueue_flags(binary_form_outer_section)
scraper.scrape_kernel_profiling_info_masks(binary_form_outer_section)
scraper.scrape_capabilities(binary_form_outer_section)
scraper.scrape_reserved_ray_flags(binary_form_outer_section)
scraper.scrape_reserved_ray_query_intersections(binary_form_outer_section)
scraper.scrape_reserved_ray_query_committed_types(binary_form_outer_section)
scraper.scrape_reserved_ray_query_canditate_types(binary_form_outer_section)
scraper.scrape_reserved_fragment_shading_rates(binary_form_outer_section)
scraper.scrape_reserved_fp_denorm_modes(binary_form_outer_section)
scraper.scrape_reserved_fp_operation_modes(binary_form_outer_section)
scraper.scrape_quantization_modes(binary_form_outer_section)
scraper.scrape_overflow_modes(binary_form_outer_section)
scraper.scrape_packed_vector_format(binary_form_outer_section)
scraper.scrape_instructions(binary_form_outer_section)
scraper.flush(sys.argv[1])
sys.exit(0)
