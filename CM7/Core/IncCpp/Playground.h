/*
 * Playground.h
 *
 *  Created on: May 29, 2022
 *      Author: diktux
 */
#include <stdint.h>

#ifndef SRCCPP_PLAYGROUND_H_
#define SRCCPP_PLAYGROUND_H_

class Playground
{
public:
  Playground();
  virtual ~Playground();
  uint8_t* getFields();
  uint8_t getMaxRow();
  uint8_t getMaxLine();
  uint8_t getField(uint8_t fieldNo);
  bool isOverflow();
  void killLine(uint8_t line);
  void insertLine();
  uint8_t highestPointInRow(uint8_t rowNo);
  bool isLineFull(uint8_t lineNo);
  void setField(uint8_t fieldNo, uint8_t blockType);

  //
  bool isOnBottom(uint8_t *blockArray);
  //bool isLineFull(uint8_t lineNumber); (Sven Wanzenried:) Commented because equivalent statement @line 25
  bool isSpaceRight(uint8_t *blockArray);
  bool isSpaceLeft(uint8_t *blockArray);
  bool canRotate(uint8_t *blockArrayRotated);
  uint8_t getPreview(uint8_t *blockArray, uint8_t *previewArray);

private:
  uint8_t fields[209];
  const uint8_t LINES = 21;
  const uint8_t ROWS = 10;
  const uint8_t MAX_FIELD_NO = ROWS * LINES - 1;

  uint8_t generateRandomSpaceInLine();
  uint8_t firstBlockColNewLine();
};

#endif /* SRCCPP_PLAYGROUND_H_ */
