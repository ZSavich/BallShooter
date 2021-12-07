# BallShooter

![Project Header](https://i.imgur.com/3zvOMyk.png)

Данный проект разработал Савич Евгений как тестовое задание на должность Junior Unreal Engine Developer.

**Версия Unreal Engine: 4.27**

# Разработанные механики на С++ 
- Класс персонажа (**SCharacter**)
- Компонент оружия (**SWeaponComponent**)
- Класс оружия (**SWeapon**)
- Класс снаряда (**SProjectile**)
- Класс цели (**STargetSphere**)
- Виджет игрока (**SPlayerWidget**)
- Игровой режим с подробными настройками (**SGameMode**)
- Класс HUD (**SGameHUD**)
- Класс статистики игрока (**SPlayerState**)

# Настройки Game Mode

![Game Mode Settings](https://i.imgur.com/eLeDr6r.png)

1. **Need Kill to Finish** - Кол-во сфер которые нужно уничтожить в радиусе *Kills Counting Radius*;
2. **Delay Between Waves** - Задержка между волнами (сек);
3. **Initial Spawn Radius** - Первоначальный радиус создания сфер;
4. **Kills Counting Radius** - Радиус в котором засчитывается уничтожение сфер для прохождения волны;
5. **Target Sphere Class** - Базовый класс сферы;
6. **Initial Targets Quantity** - Первоначальное кол-во сфер;
7. **Targets Distance** - Дистанция между сферами;
8. **Spawn Height** - Уровень высоты точки создания сфер;
9. **Min Target Size** - Минимальный размер сфер;
10. **Targets Quaninty Multi** - Увеличитель количества сфер с каждой волной (%);
11. **Radius Multi** - Увеличитель радиуса создания сфер с каждой волной (%);
12. **Target Size Multi Step** - Шаг уменьшения размера сфер при создании;