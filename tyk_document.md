# document of tyk's part
<style>
    .important{
        color:#ff0000;
    }
    .variable{
        color:#bf4fed;
    }
    .function{
        color:#dead17;
    }
</style>

## The <font class="important">variable/function</font> you need to know

you may <font class="important"><b>USE these</b></font>, so please check here <font class="important"><b>FOR SURE</b>.</font>

### CGameStateRun:
Members:

- ### <b>bool <font class="variable"> isMenu</font>=true</b>

  to control flow, default is true.
  <b>true</b>: display menu.
  <b>false</b>: depends on <font class="variable"><b>currentStage</b></font>, change to the game stage.



Functions:
- ### <b>void  <font class="function">OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)</font></b>

  change text color by pressed VK_LEFT or VK_RIGHT.
  you may MODIFY this function.

<hr>

<font class="important">
The thing you want to find will be placed up above, check there first.

If you still don't find it, then check down below.
</font>


<hr>

## The whole work
### CGameStateInit:
Members:


- ### <b>CMovingBitmap <font class="variable">title</font></b>
  the img of "undertale"

- ### <b>CMovingBitmap <font class="variable">enterCommand</font></b>
  the img of "press enter"


Functions:

- ### <b>void  <font class="function">StartMenu()</font></b>
  display title and press enter to get into the game.
  BASCIALLY you will not modify this.


### CGameStateRun:
Members:

- ### <b>CMovingBitmap <font class="variable"> menuTop</font></b>

  store the img of menu



- ### <b> CMovingBitmap <font class="variable"> menuBottom</font></b>

  store the img of menu



- ### <b> int <font class="variable">currentStage</font>=1</b>

  default is 1, the first stage.
  there are three stages, so the value will either be 1 or 2 or 3.


- ### <b>bool <font class="variable"> isMenu</font>=true</b>

  to control flow, default is true.
  <b>true</b>: display menu.
  <b>false</b>: depends on <font class="variable"><b>currentStage</b></font>, change to the game stage.

Functions:

- ### <b>void  <font class="function">OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)</font></b>

  change text color by pressed VK_LEFT or VK_RIGHT.
  you may MODIFY this function.

- ### <b>void  <font class="function">WholeMenu()</font></b>

  do the <b><font class="function">MenuState()</font></b> and <b><font class="function">ShowMenuImg()</font></b>
  BASCIALLY you will not modify this.



- ### <b>void  <font class="function">MenuState()</font></b>

  display stage text on screen
  BASCIALLY you will not modify this.



- ### <b>void  <font class="function">ShowMenuImg()</font></b>

  display <b><font class="variable">menuTop</font></b> and <b><font class="variable">menuBottom</font></b>  on screen
  BASCIALLY you will not modify this.

- ### <b>void  <font class="function">Stage1OFF()</font></b>

  display stage text in white
  BASCIALLY you will not modify this.

- ### <b>void  <font class="function">Stage2OFF()</font></b>

  display stage text in white
  BASCIALLY you will not modify this.

- ### <b>void  <font class="function">Stage3OFF()</font></b>

  display stage text in white
  BASCIALLY you will not modify this.

- ### <b>void  <font class="function">Stage1ON()</font></b>

  display stage text in yellow
  BASCIALLY you will not modify this.

- ### <b>void  <font class="function">Stage2ON()</font></b>

  display stage text in yellow
  BASCIALLY you will not modify this.

- ### <b>void  <font class="function">Stage3ON()</font></b>

  display stage text in yellow
  BASCIALLY you will not modify this.