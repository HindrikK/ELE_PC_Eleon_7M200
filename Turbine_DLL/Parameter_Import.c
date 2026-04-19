#include <Parameter_Import.h>


#define PAR_FILE_LINEMAX 50
int Import_Parameters_File(const char fileName[], unsigned int maxCount)
{
    int result;
    FILE* fptr;
    char line[PAR_FILE_LINEMAX];
    char name[31];
    double value;
    U32 type;
    char unit[10];
    float scaling;
    unsigned int parameterCount = 0;
    U8 value_U8;
    U8 value_S8;
    U16 value_U16;
    U16 value_S16;
    U32 value_U32;
    U32 value_S32;
    F32 value_F32;
    U64 value_U64;
    U64 value_S64;
    char valueStr[51];

    // open file
    fptr = fopen(fileName, "r");
    if (fptr == NULL)
    {
        OS_DEBUGLOG_make_entry(0, "Can't open file - %s", fileName, "\n");
        return OS_FILE_NOFILE;
    }

    // read first(empty) line
    fgets(line, PAR_FILE_LINEMAX, fptr);
    
    // read file
    while (true)
    {   
        // read line
        if (fgets(line, PAR_FILE_LINEMAX, fptr) != NULL)
        {
            if (line[0] == '#')
            {
                continue;   // comment line detected; continue to look for parameter name
            }
            else if (line[0] == '\n')
            {
                continue;   // empty line detected; continue to look for parameter name
            }
            else if (line[0] == 'N' && line[1] == 'a' && line[2] == 'm' && line[3] == 'e' && line[4] == ':' && line[5] == ' ' && strlen(&line[6]) > 2)
            {
                if (sscanf(&line[6], "%s", &name) != 1)
                {
                    fclose(fptr);
                    return -1;  // invalid value
                }

                // look for variable in database
                varid_t varID;
                if (OS_VarDB_GetVariableID(name, &varID) != 0)
                {
                    return -1;  // no variable with this name exists
                }

                // get type
                if (fgets(line, PAR_FILE_LINEMAX, fptr) != NULL)
                {
                    if (line[0] == 'T' && line[1] == 'y' && line[2] == 'p' && line[3] == 'e' && line[4] == ':' && line[5] == ' ' && strlen(&line[6]) > 1)
                    {
                        char _type[10];
                        if (sscanf(&line[6], "%s", &_type) == 1)
                        {
                            if (!strcmp(_type, "BOOL")) type = TYPE_BOOL;
                            else if (!strcmp(_type, "U8")) type = TYPE_U8;
                            else if (!strcmp(_type, "S8")) type = TYPE_S8;
                            else if (!strcmp(_type, "U16")) type = TYPE_U16;
                            else if (!strcmp(_type, "S16")) type = TYPE_S16;
                            else if (!strcmp(_type, "U32")) type = TYPE_U32;
                            else if (!strcmp(_type, "S32")) type = TYPE_S32;
                            else if (!strcmp(_type, "F32")) type = TYPE_F32;
                            else if (!strcmp(_type, "U64")) type = TYPE_U64;
                            else if (!strcmp(_type, "S64")) type = TYPE_S64;
                            else if (!strcmp(_type, "F64")) type = TYPE_F64;
                            else if (!strcmp(_type, "STRING")) type = TYPE_STRING;
                            else return -1; // invalid type
                        }
                        else
                        {
                            fclose(fptr);
                            return -1;  // invalid value
                        }

                        // compare with the actual type in database
                        type_t varType;
                        result = OS_VarDB_GetVariableType(varID, &varType);
                        if (type != varType) return -1; // type mismatch
                    }
                    else
                    {
                        fclose(fptr);
                        return -1;  // invalid unit
                    }
                }
                else
                {
                    fclose(fptr);
                    return -1;  // unexpected END OF FILE
                }

                // get value
                if (fgets(line, PAR_FILE_LINEMAX, fptr) != NULL)
                {
                    if (line[0] == 'V' && line[1] == 'a' && line[2] == 'l' && line[3] == 'u' && line[4] == 'e' && line[5] == ':' && line[6] == ' ' && strlen(&line[7]) > 0)
                    {
                        if (type == TYPE_STRING)
                        {
                            if (sscanf(&line[7], "%s", &valueStr) != 1)
                            {
                                fclose(fptr);
                                return -1;  // invalid value
                            }
                        }
                        else
                        {
                            if (sscanf(&line[7], "%lf", &value) != 1)
                            {
                                fclose(fptr);
                                return -1;  // invalid value
                            }
                        }
                    }
                    else
                    {
                        fclose(fptr);
                        return -1;  // invalid unit
                    }
                }
                else
                {
                    fclose(fptr);
                    return -1;  // unexpected END OF FILE
                }

                // get scaling
                if (fgets(line, PAR_FILE_LINEMAX, fptr) != NULL)
                {
                    if (line[0] == 'S' && line[1] == 'c' && line[2] == 'a' && line[3] == 'l' && line[4] == 'i' && line[5] == 'n' && line[6] == 'g' && line[7] == ':' && line[8] == ' ' && strlen(&line[9]) > 0)
                    {
                        if (sscanf(&line[9], "%f", &scaling) != 1)
                        {
                            fclose(fptr);
                            return -1;  // invalid value
                        }
                    }
                    else
                    {
                        fclose(fptr);
                        return -1;  // invalid decimal
                    }
                }
                else
                {
                    fclose(fptr);
                    return -1;  // unexpected END OF FILE
                }

                // get unit
                if (fgets(line, PAR_FILE_LINEMAX, fptr) != NULL)
                {
                    if (line[0] == 'U' && line[1] == 'n' && line[2] == 'i' && line[3] == 't' && line[4] == ':' && line[5] == ' ' && strlen(&line[6]) > 1)
                    {
                        if (sscanf(&line[6], "%s", &unit) != 1)
                        {
                            fclose(fptr);
                            return -1;  // invalid value
                        }
                    }
                    else
                    {
                        fclose(fptr);
                        return -1;  // invalid unit
                    }
                }
                else
                {
                    fclose(fptr);
                    return -1;  // unexpected END OF FILE
                }

                parameterCount++;
                if (parameterCount >= maxCount)
                {
                    return -1;  // max number of parameters exceeded
                }

                // update parameter value in system
                switch (type)
                {
                case TYPE_BOOL:
                    value_U8 = value ? 1 : 0;
                    if (OS_VarDB_UpdateVariable(varID, &value_U8, 1) != 0) return -2;
                    break;
                case TYPE_U8:
                    value_U8 = (char)(value * scaling);
                    if (OS_VarDB_UpdateVariableByName(name, &value_U8, 1) != 0) return -3;
                case TYPE_S8:
                    value_S8 = (unsigned char)(value * scaling);
                    if (OS_VarDB_UpdateVariable(varID, &value_S8, 1) != 0) return -4;
                    break;
                case TYPE_U16:
                    value_U16 = (uint16_t)(value * scaling);
                    if (OS_VarDB_UpdateVariable(varID, &value_U16, 2) != 0) return -5;
                    break;
                case TYPE_S16:
                    value_S16 = (int16_t)(value * scaling);
                    if (OS_VarDB_UpdateVariable(varID, &value_S16, 2) != 0) return -6;
                    break;
                case TYPE_U32:
                    value_U32 = (uint32_t)(value * scaling);
                    if (OS_VarDB_UpdateVariable(varID, &value_U32, 4) != 0) return -7;
                    break;
                case TYPE_S32:
                    value_S32 = (int32_t)(value * scaling);
                    if (OS_VarDB_UpdateVariable(varID, &value_S32, 4) != 0) return -8;
                    break;
                case TYPE_F32:
                    value_F32 = (float)value;
                    if (OS_VarDB_UpdateVariableByName(name, &value_F32, 4) != 0) return -9;
                    break;
                case TYPE_U64:
                    value_U64 = (uint64_t)(value * scaling);
                    if (OS_VarDB_UpdateVariable(varID, &value_U64, 8) != 0) return -10;
                    break;
                case TYPE_S64:
                    value_S64 = (int64_t)(value * scaling);
                    if (OS_VarDB_UpdateVariable(varID, &value_S64, 8) != 0) return -11;
                    break;
                case TYPE_F64:
                    if (OS_VarDB_UpdateVariable(varID, &value, 8) != 0) return -12;
                    break;
                /*case TYPE_STRING:
                    if (OS_VarDB_UpdateString(varID, valueStr) != 0) return -13;
                    break;*/
                }
                
                continue;
            }
            else
            {
                fclose(fptr);
                return -1;  // invalid line
            }
        }
        else
        {
            if (parameterCount)
            {
                fclose(fptr);
                return parameterCount;
            }
            else
            {
                fclose(fptr);
                return -1;  // unexpected END OF FILE
            }
                
        }
    }

    fclose(fptr);

    return 0;
}