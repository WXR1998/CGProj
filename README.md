# CGProj

开题报告和论文原文见`./doc/`下的pdf。

## 运行
`> make`

## 接口

### `solver.hpp`
- `AnnulusSolver`
    * `p`是`std::vector<Point>`，是需要求解的点集
    * `Annulus solve()` 用于求解最大空环
    - `SquareAnnulusSolver : AnnulusSolver`
    - `RectAnnulusSolver : AnnulusSolver`
### `utils.hpp`
- `Rect`
    * 矩形，其有四个参数x1, y1, x2, y2，分别代表最小x，最小y，最大x，最大y。(x1, y1)就是矩形的左下角点，(x2, y2)是矩形的右上角点。
- `Annulus`
    * 空环，`SolutionType type`参数代表这个空环的形状。其有几种特殊情况需要处理
        - 长条形(STRIPE_XXXXX)，此时其元素`Point a, b`分别在这个长条的两条平行线上
        - L形(L_SHAPED_X)，此时元素`Point a, b`分别是这个L形区域的两个顶点，type: L_SHAPED_1，2，3，4分别表示这个L形区域是朝向第一象限，第二象限...
        - 普通环形(NORMAL)，此时元素`Rect inner, outer`分别是内矩形和外矩形。保证inner矩形是在outer矩形的内部

## 注意事项
    为了计算时不出现小数，所有输入的点的坐标需要是偶数，但最后输出的正方形、矩形的中心位置坐标可能是奇数。输入输出时需要注意。


## 分工
- 算法实现      王宣润
- UI实现        李哲
- 文献综述和报告撰写    李玮祺