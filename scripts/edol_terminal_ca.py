from pathlib import Path
import os

Import("env")


def enabled(value):
    return value.strip().lower() in {"1", "true", "yes"}


ca_file = os.environ.get("EDOL_AMS_ROOT_CA_FILE", "").strip()
secure_build = enabled(os.environ.get("EDOL_TERMINAL_SECURE_BUILD", ""))

if secure_build and not ca_file:
    raise RuntimeError(
        "EDOL_TERMINAL_SECURE_BUILD requires EDOL_AMS_ROOT_CA_FILE with the deployment CA PEM"
    )

if ca_file:
    path = Path(ca_file).expanduser().resolve()
    if not path.is_file():
        raise RuntimeError("EDOL_AMS_ROOT_CA_FILE does not name a readable PEM file")

    certificate = path.read_text(encoding="utf-8").replace("\r\n", "\n").strip()
    if "-----BEGIN CERTIFICATE-----" not in certificate or "-----END CERTIFICATE-----" not in certificate:
        raise RuntimeError("EDOL_AMS_ROOT_CA_FILE must contain a PEM certificate")

    escaped = certificate.replace("\\", "\\\\").replace('"', '\\"').replace("\n", "\\n")
    env.Append(CPPDEFINES=[("EDOL_AMS_ROOT_CA_PEM", '\\"' + escaped + '\\"')])
