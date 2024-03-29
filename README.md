# Sample of a C++ project referencing a Native AOT compiled DLL

## Building from command line

```
cd CppApplication
msbuild CppApplication.vcxproj
```

The important bit in the vcxproj is this:

```xml
  <PropertyGroup>
    <DisableFastUpToDateCheck>true</DisableFastUpToDateCheck>
  </PropertyGroup>

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
             Properties="RuntimeIdentifier=win-$(Platform)"
             Targets="Restore" />

    <MSBuild Projects="@(NativeAotProjectReference)"
             Properties="_IsPublishing=true;RuntimeIdentifier=win-$(Platform)"
             Targets="Build;Publish">
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
