# Sample of a C++ project referencing a Native AOT compiled DLL

Known issues:

* When building in Visual Studio, no rebuild of the managed portion happens for some reason

## Building from command line

```
cd CppApplication
msbuild CppApplication.vcxproj
```

The important bit in the vcxproj is this:

```xml
  <ItemGroup>
    <NativeAotProjectReference Include="../PublishAotLibrary/PublishAotLibrary.csproj" />
  </ItemGroup>

  <PropertyGroup>
    <ComputeLinkInputsTargets>
      $(ComputeLinkInputsTargets);
      BuildNativeAotProject
    </ComputeLinkInputsTargets>
  </PropertyGroup>
	
  <Target Name="BuildNativeAotProject">
    <MSBuild Projects="@(NativeAotProjectReference)"
             Properties="_IsPublishing=true;RuntimeIdentifier=win-$(Platform)"
             Targets="Restore;Build;Publish">
      <Output TaskParameter="TargetOutputs" ItemName="NativeAotProjectOutputs" />
    </MSBuild>

    <ItemGroup>
      <Link Include="@(NativeAotProjectOutputs->'%(RootDir)%(Directory)native\%(Filename).lib')"
            Condition="%(NativeAotProjectOutputs.MSBuildSourceTargetName) == 'Build'" />
    </ItemGroup>

    <Copy SourceFiles="@(NativeAotProjectOutputs->'%(RootDir)%(Directory)native\%(Filename).dll')"
          DestinationFolder="$(OutputPath)" />
  </Target>
```
