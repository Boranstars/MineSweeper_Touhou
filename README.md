# MineSweeper_Touhou

![C++](https://img.shields.io/badge/language-C++20-blue.svg)
![Qt](https://img.shields.io/badge/framework-Qt6.8-green.svg)
![CMake](https://img.shields.io/badge/build-CMake-orange.svg)

一个使用了东方元素的扫雷小游戏，基于 WHUT 计算机编程强化训练大作业。

---

## 总体架构

```mermaid
graph TB
    %% 定义样式
    classDef coreClass fill:#cde4ff,stroke:#333,stroke-width:2px;
    classDef uiClass fill:#ffd8b1,stroke:#333,stroke-width:2px;
    classDef utilClass fill:#d1f0d1,stroke:#333,stroke-width:2px;
    classDef interfaceClass fill:#f0f0f0,stroke:#666,stroke-width:1px,stroke-dasharray: 5 5;

    %% 核心逻辑层 (Core Layer)
    subgraph Core [核心逻辑层]
        GB(GameBoard<br/>游戏逻辑控制器):::coreClass
        MU(MineUnit<br/>游戏单元):::coreClass
    end

    %% 表示层/用户界面层 (GUI Layer)
    subgraph GUI [表示层]
        MW(MainWindow<br/>主窗口控制器):::uiClass
        SW(SceneWidget<br/>游戏板渲染部件):::uiClass

        CD(CustomDialog<br/>设置对话框):::uiClass
        WD(WinDialog<br/>胜利对话框):::uiClass
        LD(LostDialog<br/>失败对话框):::uiClass

        MW --> SW
    end

    %% 工具层 (Utils Layer)
    subgraph Utils [工具层]
        RL(ResourceLoader<br/>资源加载器):::utilClass
    end

    %% 外部资源
    RES(Images/Styles<br/>图片与样式资源)

    %% 定义接口（信号与槽）
    SI1(游戏状态信号<br/>e.g., unitUpdated, gameWon):::interfaceClass
    SI2(用户输入事件<br/>e.g., onCellClicked):::interfaceClass

    %% 核心交互关系
    GB -- "包含 N*M 个" --> MU
    GB -- "发射" --> SI1
    SW -- "监听/触发" --> SI2
    SI1 -- "接收并处理" --> SW
    SI1 -- "接收并处理" --> MW
    SI1 -- "接收并触发" --> WD
    SI1 -- "接收并触发" --> LD

    SI2 -- "接收并处理" --> GB

    MW -- "调用弹出" --> CD
    CD -- "提供新配置参数" --> GB

    SW -- "请求资源" --> RL
    MW -- "请求资源" --> RL
    WD -- "请求资源" --> RL
    LD -- "请求资源" --> RL
    CD -- "请求资源" --> RL
    RL -- "加载" --> RES

    %% 注释
    linkStyle 6,7,8,9,10,11,12,13,14,15 stroke:#777,stroke-width:1px,stroke-dasharray: 0;
    linkStyle 2,3,4,5 stroke:#333,stroke-width:2px;


```

## 功能特点

- 经典扫雷玩法，融入东方风格
- 支持多种难度（简单、普通、困难、自定义）
- 月相主题皮肤
- 排行榜功能（计划中）

## Todo 列表

- [x] 实现扫雷核心逻辑（地雷生成、揭开、标记、胜负判断）
- [x] 支持难度切换（简单、普通、困难、自定义）
- [ ] 前后端分离
- [x] 完成 UI 界面（网格绘制、鼠标交互、状态栏）
  - [x] 网格绘制
  - [x] 鼠标交互
  - [x] 状态栏
- [x] 实现月相主题皮肤（新月、上弦月、满月、残月）
- [ ] 添加排行榜功能（记录用时和难度）
- [x] 实现暂停和继续游戏功能

## 东方相关说明

本项目受《东方 Project》启发，采用月相主题设计，但不包含任何受版权保护的东方 Project 内容。所有资源（如图标、音效）均计划使用 CC0 许可的公开资源。

## 许可证

本项目采用 MIT 许可证。

