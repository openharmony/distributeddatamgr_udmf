#!/usr/bin/env python3
"""Compress uniform data type declarations into the indexed UTD format."""

import argparse
import json
from pathlib import Path


FIELDS = [
    "typeId",
    "belongingToTypes",
    "filenameExtensions",
    "mimeTypes",
    "description",
    "referenceURL",
    "iconFile",
    "ownerBundle",
    "installerBundles",
]


def get_case_insensitive(record, field):
    matches = [value for key, value in record.items() if key.casefold() == field.casefold()]
    if len(matches) > 1:
        raise ValueError(f"duplicate field ignoring case: {field}")
    return matches[0] if matches else None


def compress(declarations):
    strings = []
    indexes = {}

    def intern(value):
        if value not in indexes:
            indexes[value] = len(strings)
            strings.append(value)
        return indexes[value]

    records = []
    type_ids = set()
    for declaration in declarations:
        type_id = get_case_insensitive(declaration, "typeId")
        if not isinstance(type_id, str) or not type_id:
            raise ValueError("every declaration must have a non-empty typeId")
        if type_id in type_ids:
            raise ValueError(f"duplicate typeId: {type_id}")
        type_ids.add(type_id)

        encoded = []
        for field in FIELDS:
            value = get_case_insensitive(declaration, field)
            if isinstance(value, str):
                encoded.append(intern(value))
            elif isinstance(value, list):
                if not all(isinstance(item, str) and item for item in value):
                    raise ValueError(f"{type_id}.{field} must contain non-empty strings")
                encoded.append([intern(item) for item in value] if value else None)
            elif value is None:
                encoded.append(None)
            else:
                raise ValueError(f"unsupported value for {type_id}.{field}")
        while encoded and encoded[-1] is None:
            encoded.pop()
        records.append(encoded)

    return {"fields": FIELDS, "strings": strings, "records": records}


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("input", type=Path)
    parser.add_argument("output", type=Path)
    args = parser.parse_args()

    root = json.loads(args.input.read_text(encoding="utf-8"))
    declarations = root["UniformDataTypeDeclarations"]
    if not isinstance(declarations, list):
        raise ValueError("input declarations must be an array")
    encoded = {"UniformDataTypeDeclarations": compress(declarations)}
    args.output.write_text(json.dumps(encoded, ensure_ascii=False, separators=(",", ":")) + "\n", encoding="utf-8")


if __name__ == "__main__":
    main()
